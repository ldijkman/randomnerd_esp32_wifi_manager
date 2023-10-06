/*
original:
https://github.com/ukandrewc/Ace-Scrollbars
https://github.com/ukandrewc/Ace-Scrollbars/blob/master/src/ext-scrollbar.js

changes made by luberth
https://ldijkman.github.io/Ace_Seventh_Heaven/Hell.html

my editor does not start at mousepos/windowpos y zero
so i treid to make an offset for that

problem with scrollbar viewport on fontsize
only seems to work ok at fontsize 12
treid to change from pixel positions to percent positions
not perfect yet
but works a bit better i think

i am a mechanic, i screw things
   made some changes to make it read better for me
      not optimized for speed

https://m.facebook.com/luberth.dijkman

*/



function AceScrollbars(e) {

///////////////////////////////////////////////////////////////////////////
// arduino alike map function == Re-maps a number from one range to another. 
// https://www.arduino.cc/reference/en/language/functions/math/map/ 
///////////////////////////////////////////////////////////////////////////////
 map_range = function(value, low1, high1, low2, high2) {
    return (low2 + (high2 - low2) * (value - low1) / (high1 - low1)).toFixed(3);   // to 3 decimals, Math.round did not scale right
}


id = function (id) {
  return document.getElementById(id);
}
classname = function (classname) {
  return document.getElementsByClassName(classname);
}





	// Add CSS scrollbars
	e.container.insertAdjacentHTML("beforeend", "<div id='ace_pre-v' class='ace_scroll-v'></div><div id='ace_bar-v' class='ace_scroll-v ace_thumb-v'></div>")
	e.container.insertAdjacentHTML("beforeend", "<div id='ace_pre-h' class='ace_scroll-h'></div><div id='ace_bar-h' class='ace_scroll-h ace_thumb-h'></div>")
	e.container.insertAdjacentHTML("beforeend", "<div id='ace_map-row' class='ace_map-row'></div>")
	e.container.insertAdjacentHTML("beforeend", "<div id='ace_map'></div>")

	// Ace scrollbars
	let gWidth = 34
	let sc = classname("ace_scrollbar")

	let ro = new MutationObserver(function () {
		resizeScroll()
	})

	// Resize
	window.addEventListener("resize", function () {
		resizeScroll()
	})

	ro.observe(e.container, { characterData: true })
	for (s of sc) {
		ro.observe(s.firstElementChild, { attributes: true })
	}

	// Map

	let h = 0
	e.on("changeSelection", function () {
		clearTimeout(h)
		h = setTimeout(showMapItems, 500)
	})









	showMapItems = function () {
		let ht = ""
		// next e.getCopyText() could return a string of all selected words on a newline, 
		// split into array and get [0]
		let tx = e.getCopyText().split(/\r?\n/)[0];//e.getCopyText();// could return a string of all sellected words on a newline split into array
		console.log("tx ",tx);
		if (tx != "") {
			let op = e.getLastSearchOptions()
			// next e.getCopyText() could return a string of all selected words on a newline, 
			// split into array and get [0]
			op.needle = e.getCopyText().split(/\r?\n/)[0];			
			console.log("op.needle ",op.needle);
			e.$search.setOptions(op)
			let lr = -1	
			let nr_lines_vissible = editor.renderer.getLastVisibleRow() - editor.renderer.getFirstVisibleRow(); 
			for (r of e.$search.findAll(e.session)) {
				if (r.start.row != lr) {       
				                                           // nr_lines_vissible 40 lines for editor view?
					ht += "<div class='ace_map-item' style='top:" +  (map_range(r.start.row ,0,editor.session.getLength()+nr_lines_vissible, 0,100)) + "%;'></div>"
					// luberth thinks, i do not know maybe better in % no px
					// console.log("rScale",rScale);
					// console.log("getFirstVisibleRow",editor.renderer.getFirstVisibleRow());
					// console.log("getLastVisibleRow",editor.renderer.getLastVisibleRow());
					
					lr = r.start.row
				}
			}
		}
		let nr_lines_vissible = editor.renderer.getLastVisibleRow() - editor.renderer.getFirstVisibleRow(); 
		
var alarm="";
    //get warnings errors?
//console.log("editor.getSession().getAnnotations()",editor.getSession().getAnnotations());
//console.log("editor.getSession().getAnnotations().length",editor.getSession().getAnnotations().length);
for (let i = 0; i < e.getSession().getAnnotations().length; i=i+1) {
console.log("errors/warnings on line ",
editor.getSession().getAnnotations()[i].row,
" type=",
editor.getSession().getAnnotations()[i].type);

	alarm += "<div class='ace_map-item' style='top:" +  (map_range(e.getSession().getAnnotations()[i].row ,0,editor.session.getLength()+nr_lines_vissible, 0,100)) + "%;background-color:red;'></div>"
				
}
		id("ace_map").innerHTML = ht+alarm;
		id("ace_map-row").style.top = map_range(e.getCursorPosition().row,0,editor.session.getLength()+50, 0,100)+"%"
		// console.log("rScale2",rScale);
	}

	// Vertical
	let rScale = 1
		
	let vScale = 1
	let vStart = -1

	let vs = sc[0]
	let tv = id("ace_bar-v")    // tv is the gray view / handle on scrollbar, should match the editor view position

	vs.addEventListener("scroll", function (e) {//think it needes an offset here if editor does not start at top 0 of document
	//	tv.style.top = (vs.scrollTop-document.getElementById("editor").offsetTop) * vScale + "px"
	tv.style.top = (map_range(vs.scrollTop-id("editor").offsetTop,0,vs.scrollHeight+vs.clientHeight,0,100))+"%"
	// tv.style.top = (vs.scrollTop-e.offsetTop) * vScale + "px"

	})


	// Drag events
	tv.addEventListener("pointerdown", function (e) {
		tv.setPointerCapture(e.pointerId)
		vStart = e.clientY
    		//console.log("e.clientY",e.clientY);
    		//console.log("id("ace_map").offsetTop+'px'",id("ace_map").offsetTop);
    		//console.log("offsetTop",document.getElementById("editor").offsetTop);
				console.log();
    
	})

	tv.addEventListener("pointermove", function (e) {
		if (vStart != -1) {
			vs.scrollTop += (e.clientY - vStart) / vScale
			vStart = e.clientY
		}
	})

	tv.addEventListener("pointerup", function (e) {
		tv.releasePointerCapture(e.pointerId)
		vStart = -1
	})

	tv.previousElementSibling.addEventListener("mousedown", function (e) {
		// my editor does not start at zero because of my non editor buttons menu so offset needed
    vs.scrollTop = (e.clientY-id("editor").offsetTop) / vScale
	  // vs.scrollTop = (e.clientY-e.offsetTop) / vScale

	})

	// Horizontal
	let hScale = 1
	let hStart = -1

	let hs = sc[1]
	let th = id("ace_bar-h")

	resizeScroll = function () {
		vScale = vs.clientHeight / vs.scrollHeight
		if (vs.clientHeight) {
			tv.style.height = (vs.clientHeight * vScale) + "px"
			showScroll(tv, true)
		}
		else {
			showScroll(tv, false)
		}

		rScale = e.renderer.lineHeight * vScale
		// console.log("e.renderer.lineHeight",e.renderer.lineHeight);
		gWidth = e.renderer.gutterWidth
		th.previousElementSibling.style.left = gWidth + "px"
		showMapItems()
	}

	showScroll = function (e, s) {
		d = (s) ? "" : "none"
		e.style.display = d
		e.previousElementSibling.style.display = d
	}



	resizeScroll() // luberth added this on startup scrollbar was not ok only after resize window it was ok
}
