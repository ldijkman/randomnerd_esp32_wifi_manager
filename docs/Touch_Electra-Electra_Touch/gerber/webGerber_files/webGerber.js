var wG = window.wG || {};

wG.BOTTOM = 1, wG.TOP = 2;
wG.BOARD = 0, wG.COPPER = 1, wG.SOLDER = 2, wG.PASTE = 3, wG.SILK = 4, wG.OUTLINE = 5;

// Layer names.
wG.layerNames = {};
wG.layerNames[''] = 'No layer';
wG.layerNames[wG.BOTTOM+''+wG.COPPER] = 'Bottom copper';
wG.layerNames[wG.BOTTOM+''+wG.SOLDER] = 'Bottom solder mask';
wG.layerNames[wG.BOTTOM+''+wG.PASTE] = 'Bottom solder paste';
wG.layerNames[wG.BOTTOM+''+wG.SILK] =   'Bottom silk-screen';
wG.layerNames[wG.TOP+''+wG.COPPER] = 'Top copper';
wG.layerNames[wG.TOP+''+wG.SOLDER] = 'Top solder mask';
wG.layerNames[wG.TOP+''+wG.PASTE] = 'Top solder paste';
wG.layerNames[wG.TOP+''+wG.SILK] =   'Top silk-screen';
wG.layerNames[(wG.TOP|wG.BOTTOM)+''+wG.BOARD] = 'Drill';
wG.layerNames[(wG.TOP|wG.BOTTOM)+''+wG.OUTLINE] = 'Outline';

// All the layer types above.
wG.layerTypes = [
    '',
    wG.BOTTOM+''+wG.COPPER,
    wG.BOTTOM+''+wG.SOLDER,
    wG.BOTTOM+''+wG.PASTE,
    wG.BOTTOM+''+wG.SILK,
    wG.TOP+''+wG.COPPER,
    wG.TOP+''+wG.SOLDER,
    wG.TOP+''+wG.PASTE,
    wG.TOP+''+wG.SILK,
    (wG.TOP|wG.BOTTOM)+''+wG.BOARD,
    (wG.TOP|wG.BOTTOM)+''+wG.OUTLINE,
];

// Colors for the layers (comments contain fancy math for color deduction :P).
wG.colors = [];
// Board + SolderMask = #36620a
// Board*.5 + (94*.5, 152*.5, 6*.5) = #36620a
// Board = (#36620a - (94/2, 152/2, 6/2))/.5
// Board = (54-47, 98-76, 10-3)*2
// Board = (7*2, 22*2, 7*2)
// Board = (14, 44, 14) = #0e2c0e
wG.colors[wG.BOARD]  = '#0e2c0e';//'#203020';//'#255005';
// Copper = #b87333
wG.colors[wG.COPPER] = '#b87333';//'#c0b030'
// Copper + SolderMask = #8b861d
// SolderMask*.5 + (184*.5, 115*.5, 51*.5) = #8b861d
// SolderMask = (#8b861d - (184/2, 115/2, 51/2))/.5
// SolderMask = (139-92, 134-58, 29-26)*2
// SolderMask = (47*2, 76*2, 3*2) = (94, 152, 6)
wG.colors[wG.SOLDER] = 'rgba(94, 152, 6, .5)';//'rgba(37, 80, 5, .7)';
wG.colors[wG.PASTE]  = '#e6e8fa';
wG.colors[wG.SILK]   = '#ffffff';

// Guesses a layer's type from its filename.
wG.guessLayer = function guessLayer(f) {
    f = f.toLowerCase();
    if(f.match(/\.drl|\.drd|\.txt/))
        return [wG.BOTTOM|wG.TOP, wG.BOARD];
    if(f.match(/\.out|outline/))
        return [wG.BOTTOM|wG.TOP, wG.OUTLINE];
    if(f.match(/\.gbl|\.sol/) || f.match(/bot/) && f.match(/copper|signal/))
        return [wG.BOTTOM, wG.COPPER];
    if(f.match(/\.gbs|\.sts/) || f.match(/bot/) && f.match(/s(?:old(?:er|)|)ma?(?:sk|ks)/))
        return [wG.BOTTOM, wG.SOLDER];
    if(f.match(/\.gbp|\.crs/) || f.match(/bot/) && f.match(/pas/))
        return [wG.BOTTOM, wG.PASTE];
    if(f.match(/\.gbo|\.pls/) || f.match(/bot/) && f.match(/si?lk/))
        return [wG.BOTTOM, wG.SILK];
    if(f.match(/\.gtl|\.cmp/) || f.match(/top/) && f.match(/copper|signal/))
        return [wG.TOP, wG.COPPER];
    if(f.match(/\.gts|\.stc/) || f.match(/top/) && f.match(/s(?:old(?:er|)|)ma?(?:sk|ks)/))
        return [wG.TOP, wG.SOLDER];
    if(f.match(/\.gtp|\.crc/) || f.match(/top/) && f.match(/pas/))
        return [wG.TOP, wG.PASTE];
    if(f.match(/\.gto|\.plc/) || f.match(/top/) && f.match(/si?lk/))
        return [wG.TOP, wG.SILK];
};

// Loads a Excellon drill file.
wG.loadDrill = function loadDrill(text) {
    text = text.replace(/^[\s%]*M48/, '');
    text = text.replace(/[^\S\n]+/g, '');
    
    function numVal(x) {
        if(x[0] == '+')
            return numVal(x.slice(1));
        if(x[0] == '-')
            return -numVal(x.slice(1));
        if(x == '0')
            return 0;
        if(g.omitLead)
            while(x.length < g.num)
                x = '0'+x;
        else
            while(x.length < g.num)
                x += '0';
        return parseFloat(x.slice(0, g.int)+'.'+x.slice(g.int), 10);
    }
    
    var cmds = text.split('\n');
    
    var g = {offA: 0, offB: 0, shapes: [], cmds: [], scale: 1}, shape, body = false, prevX = 0, prevY = 0;
    
    for(var i = 0; i < cmds.length; i++) {
        var d = cmds[i];
        if(!body) {
            if(d[0] == 'T') {
                var r = /^T(\d+)[^C]*C([\d.]+)/.exec(d); // assert(r);
                g.shapes[parseInt(r[1], 10)] = ['C', +r[2]];
            }
            else if(d == 'METRIC,LZ')
                g.scale = 1, g.omitLead = false, g.int = 3, g.dec = 3, g.num = 6;
            else if(d == 'METRIC,TZ' || d == 'M71')
                g.scale = 1, g.omitLead = true, g.int = 3, g.dec = 3, g.num = 6;
            else if(d == 'INCH,LZ')
                g.scale = 25.4, g.omitLead = false, g.int = 2, g.dec = 4, g.num = 6;
            else if(d == 'INCH,TZ' || d == 'M72')
                g.scale = 25.4, g.omitLead = true, g.int = 2, g.dec = 4, g.num = 6;
            else if(d == '%')
                body = true;
        } else {
            function getNum(offset) {
                var r = /^[-+\d]*/.exec(d = d.slice(offset)); // assert(r);
                d = d.slice(r[0].length);
                return numVal(r[0]);
            }
            if(d[0] == 'T')
                shape = parseInt(d.slice(1), 10);
            else if(d[0] == 'R') {
                var r = /^\d+/.exec(d = d.slice(1)); // assert(r);
                var nr = parseInt(r[0], 10), dx = 0, dy = 0;
                d = d.slice(r[0].length);
                if(d[0] == 'X')
                    dx = getNum(1);
                if(d[0] == 'Y')
                    dy = getNum(1);
                
                // assert(!d.length);
                for(var x = prevX, y = prevY, j = 0; j < nr; j++)
                    x += dx, y += dy, g.cmds.push([(1<<2) | 3, shape, x, y]);
                prevX = x, prevY = y;
            }
            else {
                var x = prevX, y = prevY, coords = false;
                if(d[0] == 'X')
                    x = getNum(1), coords = true;
                if(d[0] == 'Y')
                    y = getNum(1), coords = true;
                if(coords) {
                    g.cmds.push([(1<<2) | 3, shape, x, y]);
                    prevX = x, prevY = y;
                }
            }
        }
    }
    return g;
};

// Loads a Gerber file.
wG.load = function load(text) {
    if(text.match(/^[\s%]*M48/))
        return wG.loadDrill(text);
    
    text = text.replace(/\s+/g, ''); // Get rid of any spaces/newlines.
    //text = text.replace(/%%+/g, ''); // Compact parameters.
    
    // Split into data and parameters sections;
    var sections = text.split('%');
    
    var g = {offA: 0, offB: 0, shapes: [], cmds: [], scale: 1}, shape = 0, macros = {}, mode = 1, inverted = false, prevX = 0, prevY = 0;
    
    function numVal(x) {
        if(x[0] == '+')
            return numVal(x.slice(1));
        if(x[0] == '-')
            return -numVal(x.slice(1));
        if(x == '0')
            return 0;
        if(g.omitLead)
            while(x.length < g.num)
                x = '0'+x;
        else
            while(x.length < g.num)
                x += '0';
        return parseFloat(x.slice(0, g.int)+'.'+x.slice(g.int), 10);
    }
    
    // Even positions are function codes, odd ones are parameters.
    for(var i = 0; i < sections.length; i++) {
        // Ignore empty sections.
        if(!sections[i].length)
            continue;
        // Get rid of data end markers at the end of data.
        sections[i][sections[i].length-1] == '*' && (sections[i] = sections[i].slice(0, -1));
        sections[i] = sections[i].split('*');
        for(var j = 0; j < sections[i].length; j++) {
            var d = sections[i][j];
            if(i%2) { // Parameters.
                if(d[0] == 'F' && d[1] == 'S') {// Format Specification.
                    var r = /^([LT]?)([AI])X(\d)(\d)Y(\d)(\d)$/.exec(d.slice(2)); // assert(r);
                    g.omitLead = !r[1] || r[1] == 'L';
                    g.abs = r[2] == 'A';
                    if(!g.abs) throw new Error('Need absolute values');
                    g.int = +r[3], g.dec = +r[4], g.num = g.int+g.dec;
                } else if(d[0] == 'O' && d[1] == 'F') {// Offset.
                    var r = /^(?:A([-+\d.]+)|)(?:B([-+\d.]+)|)$/.exec(d.slice(2)); // assert(r);
                    g.offA = parseInt(r[1], 10), g.offB = parseInt(r[2], 10);
                } else if(d == 'IPNEG') // Image Polarity.
                    throw new Error('Negative image polarity');
                else if(d[0] == 'L' && d[1] == 'P') { // Layer Polarity.
                    if(inverted && d[2] == 'D') // Switch to dark.
                        g.cmds.push([16<<2, inverted = false]);
                    else if(!inverted && d[2] == 'C') // Switch to clear.
                        g.cmds.push([16<<2, inverted = true]);
                } else if(d[0] == 'A' && d[1] == 'M') { // Aperture Macro.
                    var macro = [];
                    for(j++; j < sections[i].length; j++)
                        macro.push(sections[i][j]/*.split(',')*/);
                    macros[d.slice(2)] = macro;
                } else if(d[0] == 'A' && d[1] == 'D' && d[2] == 'D') { // Aperture Definition.
                    var r = /^(\d+)([^,]+)(?:,(.+)|)$/.exec(d.slice(3)); // assert(r);
                    var j = r[1]-10, args = [];
                    if(r[3])
                        args = r[3].split('X');
                    if(macros[r[2]]) {
                        function applyArgs(m) {
                            m = m.replace(/\$(\d+)/g, function(s, n) {
                                return +args[n-1] || 0;
                            }).toLowerCase(), repl = true;
                            while(repl == true)
                                repl = false, m = m.replace(/([\d.]+)x([\d.]+)/g, function(s, a, b) {return repl = true, a*b});
                            repl = true;
                            while(repl == true)
                                repl = false, m = m.replace(/([\d.]+)\/([\d.]+)/g, function(s, a, b) {return repl = true, a/b});
                            repl = true;
                            while(repl == true)
                                repl = false, m = m.replace(/([\d.]+)\+([\d.]+)/g, function(s, a, b) {return repl = true, a+b});
                            repl = true;
                            while(repl == true)
                                repl = false, m = m.replace(/([\d.]+)-([\d.]+)/g, function(s, a, b) {return repl = true, a-b});
                            return m;
                        }
                        var m1 = macros[r[2]], m2 = [];
                        for(var k = 0; k < m1.length; k++) {
                            var eq = /^\$(\d+)=(.+)$/.exec(m1[k]);
                            if(eq)
                                args[eq[1]-1] = +applyArgs(eq[2]);
                            else
                                m2.push(applyArgs(m1[k]).split(',').map(function(x) {return +x}));
                        }
                        g.shapes[j] = ['M', m2];
                        
                    } else
                        g.shapes[j] = [r[2]].concat(args.map(function(x) {return +x}));
                    if(j < shape)
                        shape = j;
                } else if(d == 'MOIN') // Specify Inches.
                    g.scale = 25.4;
                else if(d == 'MOMM') // Specify MMs.
                    g.scale = 1;
                else
                    console.log(d);
            } else { // Function codes.
                if(d[0] == 'G' && d[1] == '0' && d[2] == '4' || d[0] == 'M')
                    continue;
                if(d[0] == 'G' && d[1] == '5' && d[2] == '4')
                    d = d.slice(3);
                if(d == 'G70') { // Specify Inches.
                    g.scale = 25.4;
                    continue;
                }
                if(d == 'G74') { // Set Single quadrant mode.
                    mode &= ~4;
                    continue;
                }
                if(d == 'G75') { // Set Multi quadrant mode.
                    mode |= 4;
                    continue;
                }
                if(d == 'G36') { // Start Outline fill.
                    if(!(mode & 8))
                        g.cmds.push([8<<2, true]);
                    mode |= 8;
                    continue;
                }
                if(d == 'G37') { // End Outline fill.
                    if(mode & 8)
                        g.cmds.push([8<<2, false]);
                    mode &= ~8;
                    continue;
                }
                var cmode = 0;
                if(d[0] == 'G' && d.length > 4) {
                    var r = /^\d*/.exec(d = d.slice(1)); // assert(r);
                    mode = (mode & 12) | (cmode = parseInt(r[0], 10));
                    d = d.slice(r[0].length);
                }
                function getNum(offset) {
                    var r = /^[-+\d]*/.exec(d = d.slice(offset)); // assert(r);
                    d = d.slice(r[0].length);
                    return numVal(r[0]);
                }
                var x = prevX, y = prevY, oi = 0, oj = 0, hasX = false, hasY = false;
                if(d[0] == 'X')
                    x = getNum(1), hasX = true;
                if(d[0] == 'Y')
                    y = getNum(1), hasY = true;
                if(d[0] == 'I')
                    oi = getNum(1), (!(mode&2) && (x += oi, hasX = true));
                if(d[0] == 'J')
                    oj = getNum(1), (!(mode&2) && (y += oj, hasY = true));
                if(d[0] == 'D')  {// Draw.
                    if(d[1] == '0')
                        g.cmds.push([(mode<<2) | d[2], shape, x, y, oi, oj]);
                    else
                        shape = d.slice(1)-10;
                } else if(hasX && (x != prevX) || hasY && (y != prevY))
                    g.cmds.push([(mode<<2) | 1, shape, x, y, oi, oj]);
                else
                    console.log(d);
                prevX = x, prevY = y;
            }
        }
    }
    return g;
};

// Extends the limits to include all the shapes in the layer.
wG.touchLimits = function touchLimits(g, r) {
    var scale = g.scale;
    r.minX /= scale, r.minY /= scale, r.maxX /= scale, r.maxY /= scale;
    for(var i = 0; i < g.cmds.length; i++) {
        var s = g.shapes[g.cmds[i][1]];
        if(!s)
            continue;
        var x = g.cmds[i][2], y = g.cmds[i][3], rx = 0, ry = 0;
        if(s[0] == 'C')
            rx = ry = s[1]/2;
        else if(s[0] == 'R')
            rx = s[1]/2, ry = s[2]/2;
        else
            continue;
        
        if(x-rx < r.minX)
            r.minX = x-rx;
        if(y-ry < r.minY)
            r.minY = y-ry;
        if(x+rx > r.maxX)
            r.maxX = x+rx;
        if(y+ry > r.maxY)
            r.maxY = y+ry;
    }
    r.minX *= scale, r.minY *= scale, r.maxX *= scale, r.maxY *= scale;
};

// Renders one layer onto a 2D canvas.
wG.renderLayer = function renderLayer(canvas, g, limits) {
    var ctx = canvas.getContext('2d');
    
    // Use only for debugging purposes
    //var color = g.type ? wG.colors[g.type] : 'black';
    var color = 'black';
    ctx.globalCompositeOperation = 'source-over';
    ctx.fillStyle = color, ctx.strokeStyle = color;
    
    var scaleX = canvas.width / (limits.maxX-limits.minX) * g.scale, scaleY = canvas.height / (limits.maxY-limits.minY) * g.scale;
    var scaleMax = Math.max(scaleX, scaleY);
    ctx.setTransform(scaleX, 0, 0, scaleY, 0, 0);
    
    var prevX = 0, prevY = 0, minX = limits.minX/g.scale, minY = limits.minY/g.scale;
    for(var i = 0; i < g.cmds.length; i++) {
        var mode = (g.cmds[i][0] >> 2), op = g.cmds[i][0] & 3;
        if(mode == 16) { // Switch layer polarity.
            ctx.globalCompositeOperation = g.cmds[i][1] ? 'destination-out' : 'source-over';
            continue;
        }
        var x = g.cmds[i][2]-minX, y = g.cmds[i][3]-minY;
        if(mode & 8) { // Outline fill mode.
            mode &= ~8;
            if(op == 0) { // Start/End Outline fill mode.
                if(g.cmds[i][1])
                    ctx.beginPath(), ctx.moveTo(prevX, prevY);
                else
                    ctx.fill();
                continue;
            }
            if(op == 2) // Fill.
                ctx.fill(), ctx.beginPath(), ctx.moveTo(x, y);
            else if(op == 1) { // Draw.
                if(mode == 1 || mode == 5) // Linear Interpolation.
                    ctx.lineTo(x, y);
                else if(mode == 2 || mode == 3) // Single quadrant Circular Interpolation.
                    console.log('(FILL) Failed to single quadrant '+(mode==3?'CCW':'CW'), g.cmds[i], s);
                else if(mode == 6 || mode == 7) { // Multi quadrant Circular Interpolation.
                    var ox = g.cmds[i][4], oy = g.cmds[i][5], cx = prevX+ox, cy = prevY+oy;
                    ctx.arc(cx, cy, Math.sqrt(ox*ox+oy*oy), Math.atan2(-oy, -ox), Math.atan2(y-cy, x-cx), mode == 6);
                } else
                    console.log(mode);
            } else
                console.log(mode, op);
            prevX = x, prevY = y;
            continue;
        }
        var s = g.shapes[g.cmds[i][1]];
        if(!s) {
            console.log(g.cmds[i], s);
            continue;
        }
        if(op != 2) {
            if(op == 3) { // Expose.
                if(s[0] == 'C')
                    ctx.beginPath(), ctx.arc(x, y, s[1]/2, 0, Math.PI*2), ctx.fill();
                else if(s[0] == 'R')
                    ctx.beginPath(), ctx.rect(x-s[1]/2, y-s[2]/2, s[1], s[2]), ctx.fill();
                else if(s[0] == 'O') {
                    ctx.beginPath(), ctx.moveTo(x, y - s[2] / 2);
                    ctx.bezierCurveTo(x + s[1] / 2, y - s[2] / 2, x + s[1] / 2, y + s[2] / 2, x, y + s[2] / 2);
                    ctx.bezierCurveTo(x - s[1] / 2, y + s[2] / 2, x - s[1] / 2, y - s[2] / 2, x, y - s[2] / 2);
                    ctx.fill();
                } else if(s[0] == 'M') { // Aperture Macro.
                    for(var j = 0; j < s[1].length; j++) {
                        var m = s[1][j];
                        if((m[0] == 2 || m[0] == 20) && m[1]) { // Line.
                            ctx.lineWidth = m[2];
                            ctx.lineCap = 'square';
                            ctx.beginPath();
                            ctx.moveTo(x+m[3], y+m[4]), ctx.lineTo(x+m[5], y+m[6]);
                            ctx.stroke();
                        } else if(m[0] == 21 && m[1]) { // Rectangle.
                            ctx.beginPath(), ctx.rect(x+m[4]-m[2]/2, y+m[5]-m[3]/2, m[2], m[3]), ctx.fill();
                        } else if(m[0] == 4 && m[1]) { // Outline.
                            ctx.beginPath();
                            ctx.moveTo(m[3], m[4]);
                            for(var k = 1; k < m[2]; k++)
                                ctx.lineTo(m[3+k*2], m[4+k*2]);
                            ctx.fill();
                        } else if(m[0] == 5 && m[1]) { // Polygon (regular).
                            var nSides = m[2], cx = x+m[3], cy = y+m[4], r = m[5]/2;
                            ctx.beginPath();
                            var step = 2 * Math.PI / nSides, angle = m[6] * Math.PI / 180;
                            ctx.moveTo(cx +  r * Math.cos(angle), cy +  r *  Math.sin(angle));
                            for(var k = 0; k < nSides; k++) {
                                angle += step;
                                ctx.lineTo(cx + r * Math.cos(angle), cy + r * Math.sin(angle));
                            }
                            ctx.fill();
                        } else {
                            console.log('Failed to macro', m, g.cmds[i], s);
                            ctx.fillStyle = 'rgba(255, 0, 0, 1)';
                            ctx.beginPath(), ctx.arc(x, y, .5, 0, Math.PI*2), ctx.fill();
                            ctx.fillStyle = 'rgba(255, 0, 0, .2)';
                            ctx.beginPath(), ctx.arc(x, y, 1.5, 0, Math.PI*2), ctx.fill();
                            ctx.fillStyle = color;
                        }
                    }
                } else {
                    console.log('Failed to expose', g.cmds[i], s);
                    ctx.fillStyle = 'rgba(255, 0, 0, 1)';
                    ctx.beginPath(), ctx.arc(x, y, .5, 0, Math.PI*2), ctx.fill();
                    ctx.fillStyle = 'rgba(255, 0, 0, .2)';
                    ctx.beginPath(), ctx.arc(x, y, 1.5, 0, Math.PI*2), ctx.fill();
                    ctx.fillStyle = color;
                }
            }
            else if(op == 1) { // Draw.
                if(s[0] == 'C') {
                    if(!s[1]) {
                        prevX = x, prevY = y;
                        continue;
                    }
                    
                    //HACK Copper lines get some extra thickness.
                    if(g.type == wG.COPPER)
                        ctx.lineWidth = Math.ceil(s[1]*scaleMax/3+.01)/scaleMax*3;
                    else
                        ctx.lineWidth = s[1];
                    ctx.lineCap = 'round';
                    if(mode == 1 || mode == 5) { // Linear Interpolation.
                        ctx.beginPath();
                        ctx.moveTo(prevX, prevY), ctx.lineTo(x, y);
                        ctx.stroke();
                    } else if(mode == 2 || mode == 3) { // Single quadrant Circular Interpolation.
                        console.log('Failed to single quadrant '+(mode==3?'CCW':'CW'), g.cmds[i], s);
                        ctx.fillStyle = 'rgba(255, 0, 0, 1)';
                        ctx.beginPath(), ctx.arc(x, y, .5, 0, Math.PI*2), ctx.fill();
                        ctx.fillStyle = 'rgba(255, 0, 0, .2)';
                        ctx.beginPath(), ctx.arc(x, y, 1.5, 0, Math.PI*2), ctx.fill();
                        ctx.fillStyle = color;
                    } else if(mode == 6 || mode == 7) { // Multi quadrant Circular Interpolation.
                        var ox = g.cmds[i][4], oy = g.cmds[i][5], cx = prevX+ox, cy = prevY+oy;
                        ctx.beginPath();
                        ctx.arc(cx, cy, Math.sqrt(ox*ox+oy*oy), Math.atan2(-oy, -ox), Math.atan2(y-cy, x-cx), mode == 6);
                        ctx.stroke();
                    } else {
                        console.log('Failed to draw with circle', g.cmds[i], s);
                        ctx.fillStyle = 'rgba(255, 0, 0, 1)';
                        ctx.beginPath(), ctx.arc(x, y, .5, 0, Math.PI*2), ctx.fill();
                        ctx.fillStyle = 'rgba(255, 0, 0, .2)';
                        ctx.beginPath(), ctx.arc(x, y, 1.5, 0, Math.PI*2), ctx.fill();
                        ctx.fillStyle = color;
                    }
                } else {
                    console.log('Failed to draw', g.cmds[i], s);
                    ctx.fillStyle = 'rgba(255, 0, 0, 1)';
                    ctx.beginPath(), ctx.arc(x, y, .5, 0, Math.PI*2), ctx.fill();
                    ctx.fillStyle = 'rgba(255, 0, 0, .2)';
                    ctx.beginPath(), ctx.arc(x, y, 1.5, 0, Math.PI*2), ctx.fill();
                    ctx.fillStyle = color;
                }
            }
            else {
                console.log('Failed to '+mode+' '+type, g.cmds[i], s);
                ctx.fillStyle = 'rgba(255, 0, 0, 1)';
                ctx.beginPath(), ctx.arc(x, y, .5, 0, Math.PI*2), ctx.fill();
                ctx.fillStyle = 'rgba(255, 0, 0, .2)';
                ctx.beginPath(), ctx.arc(x, y, 1.5, 0, Math.PI*2), ctx.fill();
                ctx.fillStyle = color;
            }
        }
        prevX = x, prevY = y;
    }
    
    // Color the canvas.
    ctx.fillStyle = g.type ? wG.colors[g.type] : 'black';
    ctx.globalCompositeOperation = g.type == wG.SOLDER ? 'source-out' : 'source-in';
    ctx.setTransform(1, 0, 0, 1, 0, 0);
    ctx.fillRect(0, 0, canvas.width, canvas.height);
};

// Clears a 2D canvas that is a board side texture.
wG.clearBoard = function clearBoard(canvas) {
    var ctx = canvas.getContext('2d');
    ctx.globalCompositeOperation = 'source-over';
    ctx.fillStyle = wG.colors[wG.BOARD];
    ctx.fillRect(0, 0, canvas.width, canvas.height);
};

// Renders a layer onto a 2D canvas that is a board side texture.
wG.renderBoard = function renderBoard(canvas, g, limits) {
    if(!g.canvas) {
        g.canvas = document.createElement('canvas');
        g.canvas.width = canvas.width, g.canvas.height = canvas.height;
        wG.renderLayer(g.canvas, g, limits);
    }
    var ctx = canvas.getContext('2d');
    ctx.globalCompositeOperation = g.type ? 'source-over' : 'destination-out';
    if(canvas.invertedY)
        ctx.setTransform(1, 0, 0,-1, 0, canvas.height);
    else
        ctx.setTransform(1, 0, 0, 1, 0, 0);
    ctx.drawImage(g.canvas, 0, 0);
};

wG.ppmm = 40; // Pixels per mm.
wG.maxTexSize = 4096, wG.minTexSize = 256; // Largest possible texture size.

// Finds the closest power of two to the given size of a texture (needed for mipmapping).
wG.texSize = function texSize(x) {
    x = Math.min(Math.max(x, wG.minTexSize), wG.maxTexSize);
    var r = 1;
    while(r < x)
        r <<= 1;
    return r;
};

// Creates a 2D canvas that is a board side texture, for the given width and height.
wG.makeBoard = function makeBoard(w, h, invertedY) {
    var canvas = document.createElement('canvas');
    //canvas.width = w*wG.ppmm, canvas.height = h*wG.ppmm;
    /*var maxSize = Math.max(w*wG.ppmm, h*wG.ppmm) >> 1, size = 1;
    while(size < maxSize && size < wG.maxTexSize)
        size <<= 1;*/
    canvas.width = wG.texSize(w*wG.ppmm), canvas.height = wG.texSize(h*wG.ppmm);
    
    // Don't allow mipmapping for stretched textures.
    var stretch = canvas.width/canvas.height;
    if(stretch > 4)
        canvas.width--;
    else if(stretch < .25)
        canvas.height--;
    canvas.invertedY = invertedY;
    
    // Debugging: adds canvas to the page.
    /*canvas.className = 'layer';
    document.body.appendChild(canvas);*/
    return canvas;
};

// Finds the largest continuous sequence of lines that forms a loop (i.e. most likely the outline of the board).
wG.findOutline = function findOutline(layers) {
    var best = {path: [], minX: Infinity, minY: Infinity, maxX: -Infinity, maxY: -Infinity, area: 0}; // Best outline.
    var oPath, oPrev, oMinX, oMinY, oMaxX, oMaxY; // Current outline.
    function reset() {
        oPath = [], oPrev = undefined;
        oMinX = oMinY = Infinity;
        oMaxX = oMaxY = -Infinity;
    }
    for(var i = 0; i < layers.length; i++) {
        reset();
        var cmds = layers[i].cmds, shapes = layers[i].shapes, scale = layers[i].scale, half = scale/2, prevX = 0, prevY = 0;
        for(var j = 0; j < cmds.length; j++) {
            var cmd = cmds[j], mode = cmd[0] >> 2, x = cmd[2]*scale, y = cmd[3]*scale;
            if(mode != 1 && mode != 5 && mode != 6 && mode != 7) { // Look only for lines.
                reset(), prevX = x, prevY = y;
                continue;
            }
            if((cmd[0] & 3) != 1) {
                ((cmd[0] & 3) == 2 || reset()), prevX = x, prevY = y;
                continue;
            }
            var s = shapes[cmd[1]];
            if(s[0] != 'C') { // Look only for lines with circle ends.
                reset(), prevX = x, prevY = y;
                continue;
            }
            var r = s[1]*half;
            if(!r) { // Look only for visible lines.
                reset(), prevX = x, prevY = y;
                continue;
            }
            if(x-r < oMinX)
                oMinX = x-r;
            if(y-r < oMinY)
                oMinY = y-r;
            if(x+r > oMaxX)
                oMaxX = x+r;
            if(y+r > oMaxY)
                oMaxY = y+r;
            var line = [prevX, prevY, x, y, r];
            if(mode == 6 || mode == 7)
                line.push(cmd[4]*scale, cmd[5]*scale, mode == 6);
            
            // Try to connect it with the previous line.
            if(oPrev) {
                var dx = oPrev[2]-prevX, dy = oPrev[3]-prevY, sr = (r+oPrev[4]);
                if(dx*dx+dy*dy <= sr*sr)
                    oPath.push(oPrev = line);
                else if(oPath.length == 1 && (dx = oPrev[0]-prevX, dy = oPrev[1]-prevY, sr = (r+oPrev[4]), (dx*dx+dy*dy <= sr*sr))) { // Hack for some weird outlines.
                    var px = oPrev[2], py = oPrev[3];
                    oPrev[2] = oPrev[0], oPrev[3] = oPrev[1];
                    oPrev[0] = px, oPrev[1] = py;
                    oPath.push(oPrev = line);
                } else {
                    reset(), prevX = x, prevY = y;
                    continue;
                }
                // Try to connect it with the first line in this outline.
                if(oPath.length) {
                    dx = oPath[0][0]-x, dy = oPath[0][1]-y, sr = (r+oPath[0][4]);
                    if(dx*dx+dy*dy <= sr*sr) {
                        var area = (oMaxX - oMinX)*(oMaxY - oMinY);
                        // Is this outline larger?
                        if(area > best.area) {
                            best.path = oPath;
                            best.minX = oMinX, best.minY = oMinY, best.maxX = oMaxX, best.maxY = oMaxY;
                            best.area = area;
                            reset();
                        }
                    }
                }
            } else
                oPath.push(oPrev = line);
            prevX = x, prevY = y;
        }
    }
    return best;
};

// Renders an outline onto a 2D canvas that is a board side texture, by removing everything outside the outline.
wG.renderOutline = function renderOutline(canvas, outline, limits) {
    //if(!outline.path.length)
    //    return;
    var ctx = canvas.getContext('2d');
    ctx.fillStyle = 'black';
    ctx.globalCompositeOperation = 'destination-in';
    var scaleX = canvas.width / (limits.maxX-limits.minX), scaleY = canvas.height / (limits.maxY-limits.minY);
    if(canvas.invertedY)
        ctx.setTransform(scaleX, 0, 0,-scaleY, 0, canvas.height);
    else
        ctx.setTransform(scaleX, 0, 0, scaleY, 0, 0);
    ctx.beginPath();
    ctx.moveTo(outline.path[0][0]-limits.minX, outline.path[0][1]-limits.minY);
    for(var i = 0; i < outline.path.length; i++) {
        var cmd = outline.path[i];
        if(cmd.length > 5) {
            var ox = cmd[5], oy = cmd[6], cx = cmd[0]+ox, cy = cmd[1]+oy;
            ctx.arc(cx-limits.minX, cy-limits.minY, Math.sqrt(ox*ox+oy*oy), Math.atan2(-oy, -ox), Math.atan2(cmd[3]-cy, cmd[2]-cx), cmd[7]);
        } else
            ctx.lineTo(cmd[2]-limits.minX, cmd[3]-limits.minY);
    }
    ctx.fill();
};

// Little debug function.
function debug(x) {
    if(wG.debugLog)
        wG.debugLog.append($('<div>').text(x));
}

function init(layers) {
    var limits = {minX: Infinity, minY: Infinity, maxX: -Infinity, maxY: -Infinity};outlineLayers = layers.filter(function(x) {return x.type == wG.OUTLINE});
    if(outlineLayers.length)
        layers = layers.filter(function(x) {return x.type != wG.OUTLINE});
    else
        outlineLayers = layers;
    for(var i = 0; i < layers.length; i++) {
        wG.touchLimits(layers[i], limits);
        layers[i].enabled = true;
    }
    var w = limits.maxX-limits.minX, h = limits.maxY-limits.minY;
    
    var renderer, has3D = true;
    try {
        renderer = new THREE.WebGLRenderer({antialias: true});
        //wG.ppmm = 20;
        renderer.sortObjects = false;
    } catch(e) {
        debug('Got WebGL error, falling back to 2D canvas.');
        has3D = false;
        wG.ppmm = 20;
        renderer = new THREE.CanvasRenderer({antialias: true});
    }
    
    var scene = new THREE.Scene(), camera = new THREE.PerspectiveCamera(40);
    camera.up.set(0, 0, -1);
    scene.add(camera);
    
    // Ambient light.
    var ambientLight = new THREE.AmbientLight(0xcccccc);
    scene.add(ambientLight);
    
    // Sun light.
    if(has3D) {
        var sunLight = new THREE.SpotLight(0xcccccc, .3);
        sunLight.position.set(0, 150000, 0);
        scene.add(sunLight);
    }
    
    // Board.
    var Material = has3D ? THREE.MeshPhongMaterial : THREE.MeshBasicMaterial;
    var bottom = wG.makeBoard(w, h), top = wG.makeBoard(w, h, true);
    var bottomTexture  = new THREE.Texture(bottom), topTexture  = new THREE.Texture(top);
    wG.clearBoard(bottom), wG.clearBoard(top);
    bottomTexture.needsUpdate = true, topTexture.needsUpdate = true;
    var materials = [
        null,
        null,
        new Material({shininess: 80, ambient: 0xaaaaaa, specular: 0xcccccc, map: topTexture}),
        new Material({shininess: 80, ambient: 0xaaaaaa, specular: 0xcccccc, map: bottomTexture}),
        null,
        null
    ];
    if(!has3D)
        materials[2].overdraw = true, materials[3].overdraw = true;
    var board = new THREE.Mesh(new THREE.CubeGeometry(w, 1.54, h, has3D ? 1 : Math.ceil(w / 3), 1, has3D ? 1 : Math.ceil(h / 3), materials, {px: 0, nx: 0, pz: 0, nz: 0}), new THREE.MeshFaceMaterial());
    board.position.y = -100;
    
    if(has3D)
        scene.add(board);
    
    // Add the sides.
    var boardMaterial = new Material({shininess: 80, ambient: 0x333333, specular: 0xcccccc, color: 0x255005});
    var boardSides = new THREE.CubeGeometry(w, 1.54, h, 1, 1, 1, undefined, {py: 0, ny: 0});
    //boardSides.computeVertexNormals();
    boardSides = new THREE.Mesh(boardSides, boardMaterial);
    board.add(boardSides);
    
    // Create all the holes.
    var holeMaterial = boardMaterial.clone();
    holeMaterial.side = THREE.BackSide;
    for(var i = 0; i < layers.length; i++)
        if(!layers[i].type)
            for(var j = 0; j < layers[i].cmds.length; j++) {
                var cmd = layers[i].cmds[j];
                if(cmd[0] != ((1<<2) | 3))
                    continue;
                var r = layers[i].scale*layers[i].shapes[cmd[1]][1]/2;
                var hole = new THREE.CylinderGeometry(r, r, 1.54, 32, 0, true);
                //hole.computeVertexNormals();
                hole = new THREE.Mesh(hole, holeMaterial);
                hole.position.x = (cmd[2]*layers[i].scale-limits.minX)-w/2;
                hole.position.z = h/2-(cmd[3]*layers[i].scale-limits.minY);
                board.add(hole);
            }
    if(!has3D)
        scene.add(board);
    
    camera.lookAt(board.position);
    
    var boardControls = new THREE.ObjectControls(board, renderer.domElement);
    boardControls.camera = camera;
    boardControls.eye = camera.position.clone().subSelf(board.position);
    
    // Window resize handler.
    $(window).resize(function() {
        renderer.setSize(window.innerWidth, window.innerHeight);
        camera.aspect = window.innerWidth / window.innerHeight;
        camera.updateProjectionMatrix();
        boardControls.screen.width = window.innerWidth, boardControls.screen.height = window.innerHeight;
        boardControls.radius = (window.innerWidth + window.innerHeight) / 4;
    }).resize();
    
    // Scrolling wheel handler.
    $(document).mousewheel(function(event, delta, deltaX, deltaY) {
        board.position.y *= 1-deltaY*.06;
    });
    
    document.body.appendChild(renderer.domElement);
    
    // Stats.
    /*var stats = new Stats;
    $(stats.domElement).css({position: 'absolute', top: 0}).appendTo('body');*/
    
    // Controls.
    var controls = $('<div class=controls>').appendTo('body'), controlsText = $('<span>').click(function() {
        controls.toggleClass('open');
        controlsText.text(controls.is('.open') ? 'Hide controls' : 'Show controls');
    }).appendTo(controls), controlsBox = $('<div>').appendTo(controls);
    controlsText.click();
    
    // "Load other files" button.
    controlsBox.append($('<button>').text('Load other files').click(function(){location.reload()}));
    
    // Layer visibility checkboxes.
    controlsBox.append('<br><br>Layers:');
    for(var i = 0; i < layers.length; i++) {
        var checkbox = $('<input type=checkbox checked>');
        $('<div>').append(/*wG.layerNames[layers[i].side+''+layers[i].type], '<br>', */checkbox.click(function() {
            this[1].enabled = this[0].is(':checked');
            repaint = 0;
        }.bind([checkbox, layers[i]])), /*layers[i].name*/wG.layerNames[layers[i].side+''+layers[i].type]).appendTo(controlsBox);
    }
    
    var outline, repaint = 0;
    // "Show outline" checkbox.
    controlsBox.append('<br>', $('<input type=checkbox>').click(function() {
        if(outline) {
            outline.enabled = outline.sides.visible = this.checked;
            boardSides.visible = !this.checked;
            repaint = this.checked ? layers.length+1 : 0;
            if(!this.checked)
                updateArea(w, h);
            else
                updateArea(outline.maxX-outline.minX, outline.maxY-outline.minY);
            return;
        }
        if(!this.checked)
            return;
        
        outline = wG.findOutline(outlineLayers);
        if(!outline.path.length)
            return outline = undefined, alert('Can\'t find any outline!');
        outline.enabled = true;
        boardSides.visible = false;
        updateArea(outline.maxX-outline.minX, outline.maxY-outline.minY);
        var outlineShape = new THREE.Shape();
        outlineShape.moveTo(outline.path[0][0]-limits.minX-w/2, h/2-(outline.path[0][1]-limits.minY));
        for(var i = 0; i < outline.path.length; i++) {
            var cmd = outline.path[i];
            if(cmd.length > 5) {
                var ox = cmd[5], oy = cmd[6], cx = cmd[0]+ox, cy = cmd[1]+oy;
                outlineShape.arc(ox, -oy, Math.sqrt(ox*ox+oy*oy), Math.atan2(oy, -ox), Math.atan2(-(cmd[3]-cy), cmd[2]-cx), !cmd[7]);
                outlineShape.moveTo(cmd[2]-limits.minX-w/2, -(cmd[3]-limits.minY-h/2));
            } else
                outlineShape.lineTo(cmd[2]-limits.minX-w/2, -(cmd[3]-limits.minY-h/2));
        }
        outline.sides = outlineShape.extrude({amount: 1.54, bevelEnabled: false, extrudeMaterial: 0, material: 1});
        outline.sides.materials = [boardMaterial, new THREE.MeshBasicMaterial({visible: false})];
        //outline.sides.computeVertexNormals();
        board.add(outline.sides = new THREE.Mesh(outline.sides, new THREE.MeshFaceMaterial()));
        outline.sides.position.y = 1.54/2;
        outline.sides.rotation.x = Math.PI/2;
        repaint = layers.length+1;
    }), 'Show outline');
    
    function small(text) {
        return $('<span>').css('font-size', 'small').append(text);
    }
    
    // Area and Cost.
    var areaBox = $('<span>');
    controlsBox.append('<br><br>Area: ', areaBox);
    function updateArea(dw, dh) {
        var areaMM2 = dw*dh, areaIN2 = areaMM2/25.4/25.4;
        areaMM2 = Math.round(areaMM2*100)/100;
        areaIN2 = Math.round(areaIN2*100)/100;
        areaBox.html('').append(small(areaIN2+' in<sup>2</sup> ('+areaMM2+' mm<sup>2</sup>)'), ' ');//'<br>Cost: ', small('$'+areaIN2*2));
    }
    updateArea(w, h);
    
    // "Save current view as image" button
    controlsBox.append('<br><br>', $('<button>').text('Save current view as image').click(function(){
        renderer.render(scene, camera);
        
        // Get the PNG data: URL.
        var data = renderer.domElement.toDataURL();
        
        // Open a new page and add the image with some text.
        var w = open();
        w.document.title = 'webGerber';
        w.document.body.innerHTML = 'To save the image, right click and press "Save image as..."<br>';
        w.document.body.appendChild($('<img>').attr('src', data)[0]);
    }));
    
    // Mouse Controls (explanation of).
    controlsBox.append('<br><br>Mouse Controls:<br>Rotate ', small('- Left mouse button + drag'), '<br>Zoom ', small('- Scroll / Middle mouse button + drag'), '<br>Pan ', small('- Right mouse button + drag'));
    
    /*Order
    controlsBox.append('<br><br><br><br>Finished with your design?<br>', small('Order your PCBs from Mayhew Labs:<br>$1.50/in<sup>2</sup> for 3 copies'));//<br>$1.60/in<sup>2</sup> for 3 copies<br>$1.20/in<sup>2</sup> for 5 copies<br>'));
    controlsBox.append('<br>', $('<button>').text('Learn More').click(function(){
        // Open a new page and add the image with some text.
        window.open("http://mayhewlabs.com/order-pcbs","_self");
    }));
    */
    // Sort by type, but after listing them.
    layers.sort(function(a, b) {
        return (a.type || 10) - (b.type || 10);
    });
    
    // Renders the scene (and repaints all the textures that need repainting.
    function render() {
        requestAnimationFrame(render);
        if(repaint !== null) {
            //controlsBox.css('color', 'grey').find('input,button').each(function() {this.disabled = true});
            loadingOverlay.show();
            if(repaint === 0)
                wG.clearBoard(bottom), wG.clearBoard(top), repaint++;//, bottomTexture.needsUpdate = true, topTexture.needsUpdate = true;
            else {
                // Skip any disabled layers.
                while(repaint <= layers.length && !layers[repaint-1].enabled)
                    repaint++;
                
                if(repaint <= layers.length) { // Repaint a layer.
                    if(layers[repaint-1].side & wG.BOTTOM)
                        wG.renderBoard(bottom, layers[repaint-1], limits);//, bottomTexture.needsUpdate = true;
                    if(layers[repaint-1].side & wG.TOP)
                        wG.renderBoard(top, layers[repaint-1], limits);//, topTexture.needsUpdate = true;
                } else if(outline && outline.enabled) { // Repaint the outline.
                    wG.renderOutline(bottom, outline, limits);//, bottomTexture.needsUpdate = true;
                    wG.renderOutline(top, outline, limits);//, topTexture.needsUpdate = true;
                }
                
                // Are we finished repainting?
                if(repaint > layers.length)
                    repaint = null,  loadingOverlay.hide(), /*controlsBox.css('color', '').find('input,button').each(function() {this.disabled = false}),*/ bottomTexture.needsUpdate = true, topTexture.needsUpdate = true;
                else
                    repaint++;
            }
        }
        boardControls.update();
        renderer.render(scene, camera);
        //stats.update();
    }
    render();
}

var loadingOverlay;

$(function() {
    // Debug log, shows up if there's ?debug at the end of the URL.
    if(location.search.match(/(\?|&)debug/))
        wG.debugLog = $('<strong>').css({width: '100%', 'text-align': 'center', position: 'absolute', 'z-index': 1000, color: '#111', 'font-family': 'monospace'}).prependTo('body');
    
    debug('Browser info: '+navigator.userAgent);
    if(typeof window.FileReader === 'undefined')
        debug('Your browser doesn\'t have file access');
    
    loadingOverlay = $('<div class=overlay>').html('<div><div>Loading, please wait...</div></div>').appendTo('body');
    
    var demoLayers = $('script[type="text/x-gerber"]');
    if(demoLayers.length)
        return void(setTimeout(function() {
            init(demoLayers.map(function() {
                var g = wG.load(this.text);
                var guess = wG.guessLayer(this.id);
                g.side = guess[0], g.type = guess[1];
                g.name = this.id;
                return g;
            }).get());
        }, 0));
    
    loadingOverlay.hide();
    
    // Step 1 box, the comments are for the original demo.
    var main = $('<div class=main>').appendTo('body').append($('<h1>').html('Step 1:<br>Drop gerber files here'/*+'<br>(or click for a demo board)'*/)/*.click(function() {
        main.remove();
        setTimeout(function() {
            init($('script[type="text/x-gerber"]').map(function() {
                var g = wG.load(this.text);
                var guess = wG.guessLayer(this.id);
                g.side = guess[0], g.type = guess[1];
                g.name = this.id;
                return g;
            }).get());
        }, 0);
    })*/);
    
    var layerSelect = $('<select>');
    for(var i = 0; i < wG.layerTypes.length; i++)
        layerSelect.append($('<option>').val(wG.layerTypes[i]).text(wG.layerNames[wG.layerTypes[i]]));
    
    // Stops the browser from doing anything with the dropped files (see Firefox).
    main.bind('dragover', function(ev) {
        ev.stopPropagation();
        ev.preventDefault();
    });
    
    // Drop event handler, shows the Step 2 box.
    main.bind('drop', function(ev) {
        ev.stopPropagation();
        ev.preventDefault();
        
        var step2 = $('<div>').append($('<h1>').html('Step 2:<br>Select the layers corresponding to the gerber files'));
        
        var files = ev.originalEvent.dataTransfer.files, filePairs = [];
        for(var i = 0; i < files.length; i++) {
            //if(files[i].type && !files[i].type.match(/^text/))
            //    continue;
            var fileSelect = layerSelect.clone(), guess = wG.guessLayer(files[i].name);
            if(guess)
                fileSelect.val(guess.join(''));
            step2.append('<br>', $('<strong>').text(files[i].name+'  '), fileSelect);
            filePairs.push([files[i], fileSelect]);
        }
        if(!filePairs.length)
           return alert('No valid files found!');
        
        // "Done" button.
        step2.append('<br>', $('<button>').text('Done').click(function() {
            // Count the layers.
            var layerNum = 0;
            for(var i = 0; i < filePairs.length; i++) {
                if(!filePairs[i][1].val())
                    continue;
                layerNum++;
            }
            
            // Just in case they didn't select any layer.
            if(!layerNum)
                return alert('There has to be at one selected layer!');
            
            var layers = [];
            for(var i = 0; i < filePairs.length; i++) {
                var f = filePairs[i], which = f[1].val();
                if(!which)
                    continue;
                
                var reader = new FileReader();
                reader.onload = function(ev) {
                    var g;
                    // Try to load the layer from the file.
                    try {
                        g = wG.load(ev.target.result);
                    } catch(e) {
                        loadingOverlay.hide();
                        alert('Error while loading '+this[0]+': '+e);
                        console.log(e.stack);
                        return;
                    }
                    g.type = this[2];
                    g.side = this[1];
                    g.name = this[0];
                    
                    // Do we have all the layers?
                    if(layers.push(g) >= layerNum) {
                        main.remove();
                        loadingOverlay.hide();
                        setTimeout(function() {
                            init(layers);
                        }, 0);
                    }
                }.bind([f[0].name, +which[0], +which[1]]);
                
                // Read the contents of the file, with the above callback.
                reader.readAsText(f[0]);
            }
            loadingOverlay.show();
        })).appendTo(main.html(''));
    });
});