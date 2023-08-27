  <script>
    function paste() {
      var myval = document.getElementById("myList").value;
      var htmltext;
      //console.log(myval);
      if (myval == 1) {
        //    /* */ or <!-- -->
        // test some commands
        ace.edit("editor").execCommand("toggleBlockComment");
        // editor.execCommand("showKeyboardShortcuts");
        //htmltext="<!--     -->";
        //ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
        //console.log(ace.edit("editor").getCursorPosition());
        //console.log(ace.edit("editor").selection.getCursor().column);
        //console.log(ace.edit("editor").selection.getCursor().row);
        //console.log(ace.edit("editor").selection.getCursor().column-6);
        //move cursor rom end of line  inside the comment part of paste
        //ace.edit('editor').gotoLine(ace.edit("editor").selection.getCursor().row+1,ace.edit("editor").selection.getCursor().column-6);
      }
      if (myval == 2) {
    var pastetext=`
 <!DOCTYPE html>
 <html>
 <head>
 <title>  </title>
 <style>
 body{
   background-color:orange;
   color:yellow;
 }
 </style>
 </head>
 <body>
 <center>
 <h1>Hello</h1>
 </center>
 <br>
 <a href="http://plnkr.co/edit/ZEkhoGgs4ntDZzT0" target="paste2">Paste 2 Example from<br>http://plnkr.co/edit/ZEkhoGgs4ntDZzT0<br>Electric Storm</a><br>
 </body>
 </html>
        `;
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), pastetext);
      }
      if (myval == 3) {
        htmltext = "<img src=\"https://raw.githubusercontent.com/ldijkman/Electra/main/touch_electra.gif\"><br>\n";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 4) {
        htmltext = "<a href=\"http://ldijkman.github.io/Electra\" target=\"_blank\">Electra</a><br>";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 5) {
        htmltext = "<script type=\"text/javascript\" src=\"\"></script\>\n";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 6) {
        htmltext = "&nbsp;";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 7) {
        htmltext = "&emsp;";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 8) {
        htmltext = "<p align=\"right\">Right align content</p>";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
    
         if (myval == 9) {
      htmltext = `
<iframe id="" align="left" width="500" height="320" src="https://www.youtube.com/embed/5uapPPC8eQY" style="border:none; -ms-transform: scale(1, 1); transform: scale(1, 1)" scrolling="no">
</iframe>
<br>
<br>
<h1>latest video Electric Storm</h1>
<br>
<iframe width="697" height="392" src="https://www.youtube.com/embed/eC0tJmIl_lY" title="Ace Editor Preview   WYSIWYG  Electric Storm" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen>
</iframe><br>
<br>
 <center><small>
 Electric Storm<br>
 <a href="http://plnkr.co/edit/ZEkhoGgs4ntDZzT0" target="_blank">http://plnkr.co/edit/ZEkhoGgs4ntDZzT0</a><br>
 <br>
 </center>
      `;
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 10) {
        htmltext = "<meta http-equiv=\"Refresh\" content=\"10\">\n";
        htmltext += "<!-- does not work nice in preview editor, reloads the page in 10 seconds -->\n";
        htmltext += "<!-- reload to another URL -->\n";
        htmltext += "<!-- <meta http-equiv=\"refresh\" content=\"30; URL=https://ldijkman.github.io/Electra/\"> -->\n";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 11) {
        htmltext = "<table width=\"100%\" border=\"1\" cellspacing=\"5\" summary=\"bkj\">\n";
        htmltext += "<tr>\n";
        htmltext += "<td style=\"text-align:center;\">1</td>\n";
        htmltext += "<td>2</td>\n";
        htmltext += "<td>3</td>\n";
        htmltext += "</tr>\n";
        htmltext += "<tr>\n";
        htmltext += "<td>4</td>\n";
        htmltext += "<td>5</td>\n";
        htmltext += "<td>6</td>\n";
        htmltext += "</tr>\n";
        htmltext += "</table>\n";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 12) {
        htmltext = "<p>A normal horizontal line:</p>\n";
        htmltext += "<hr>\n";
        htmltext += "<p>With CSS:</p>\n";
        htmltext += "<hr style=\"height:10px; border-width:5; border-color:rgb(17,26,158); background-color:rgb(30,212,116); width:75%;\">\n";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 13) {
        htmltext = "<h0>h0 text</h0>\n";
        htmltext += "<h1>h1 text</h1>\n";
        htmltext += "<h2>h2 text</h2>\n";
        htmltext += "<h3>h3 text</h3>\n";
        htmltext += "<h4>h4 text</h4>\n";
        htmltext += "<h5>h5 text</h5>\n";
        htmltext += "<h6>h6 text</h6>\n";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 14) {
        htmltext = "<p style=\"font-family:Courier; color:rgb(223,15,15); font-size: 20px;\">This text has the font Courier, is rgb(223,15,15), and 20px.</p>\n";
        htmltext += "<!-- https://www.w3schools.com/cssref/css_websafe_fonts.asp -->";
        htmltext += "<!--\nArial (sans-serif)\nVerdana (sans-serif)\nHelvetica (sans-serif)\nTahoma (sans-serif)\nTrebuchet MS (sans-serif)\nTimes New Roman (serif)\nGeorgia (serif)\nGaramond (serif)\nCourier New (monospace)\nBrush Script MT (cursive) \n-->\n";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 15) {
        htmltext = "<link href='https://fonts.googleapis.com/css?family=Sofia' rel='stylesheet'>\n";
        htmltext += "<p style=\"font-family: 'Sofia';font-size: 22px;\">Lorem ipsum dolor sit amet, consectetuer adipiscing elit.</p>\n";
        htmltext += "<!-- https://developers.google.com/fonts/docs/getting_started -->\n";
        htmltext += "<!-- https://www.w3schools.com/css/css_font_google.asp -->";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 16) {
        htmltext = "<link rel=\"stylesheet\" href=\"https://fonts.googleapis.com/css?family=Sofia&effect=fire\">\n";
        htmltext += "<font size=\"77px\" style=\"font-family: \"Sofia\", sans-serif; font-size: 30px;\" class=\"font-effect-fire\">Russia on Fire</font>\n";
        htmltext += "<p style=\"font-family: \"Sofia\", sans-serif; font-size: 30px;\" class=\"font-effect-fire\">Burn MF burn.</p>\n";
        htmltext += "<p style=\"font-family: \"Sofia\", sans-serif; font-size: 30px;\" class=\"font-effect-fire\">123</p>\n";
        htmltext += "<!-- https://www.w3schools.com/css/css_font_google.asp -->\n";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 17) {
        htmltext = "<style>/* style css shoudl be in the head */\n";
        htmltext += "body{\n";
        htmltext += "background-color:rgb(13,13,12);\n";
        htmltext += "color:yellow;\n";
        htmltext += "}\n";
        htmltext += "</style>\n";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 18) {
        // test for mark linenumbers and easy scroll to edit positions
        htmltext = "<!-- mark/unmark gutter linenumbers with mouseclick -->\n";
        htmltext += "<!-- want to make a scroll up down button for easy scroll -->\n";
        htmltext += "<!-- to marked line numbers -->\n";
        htmltext += "<!-- for easy code edit jumping -->\n";
        htmltext += "<!-- for now jump to line 20 -->\n";
        htmltext += "<!-- JumpSrroll to Marked linenumbers by mouseclick Electrric Storm -->\n";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
        ace.edit("editor").scrollToLine(20, true, true, );
        ace.edit("editor").gotoLine(20, 0, true);
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 19) {
        htmltext = "<style>\na:hover {\n background-color: yellow;\n}\n</style>\n\n";
        htmltext += "<h1>\n<a href=\"https://codepen.io/ldijkman/pen/dymRoeR\" target=\"new1\">linktext one</a><br><br>\n<a href=\"https://codepen.io/ldijkman/pen/dymRoeR\" target=\"new2\">linktext two</a>\n</h1>";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 20) {
        htmltext = "<!DOCTYPE HTML> \n";
        htmltext += "<html> <!-- start and end document--> \n";
        htmltext += "<head>\n";
        htmltext += "<title> titel of the page </title>\n";
        htmltext += "<style>/* style css shoudl be in the head */\n";
        htmltext += "body{\n";
        htmltext += "  background-color: rgb(47,52,107);\n";
        htmltext += "  color: rgb(234,245,19);\n";
        htmltext += "}\n";
        htmltext += "</style>\n";
        htmltext += "</head><!-- end head start body -->\n";
        htmltext += "<body><!-- end head start body -->\n";
        htmltext += "<h1>Hello h1 text</h1>\n";
        htmltext += "<h2>h2 text</h2>\n";
        htmltext += "<h3>h3 text</h3>\n";
        htmltext += "<h4>h4 text</h4>\n";
        htmltext += "<h5>h5 text</h5>\n";
        htmltext += "<h6>h6 text</h6>\n";
        htmltext += "<hr> hr is a horizontal line ruler <br>\n";
        htmltext += "<center> center text </center> \n";
        htmltext += "<p> Paragraph 1 </p>\n";
        htmltext += "<p> Paragraph 2 </p>\n";
        htmltext += "<p> Paragraph 3</p>\n";
        htmltext += "br break the line to new line<br>\n";
        htmltext += "&nbsp; is a space <br>\n";
        htmltext += "<strike> strike trough text </strike><br>\n";
        htmltext += "<b> bold text </b><bbr>\n";
        htmltext += "<i> italic text</i><br>\n";
        htmltext += "<u>underline text</u><br>\n";
        htmltext += "<li> list item </li><br>\n";
        htmltext += "<blockquote>blockquote</blockquote><br>\n";
        htmltext += " </body> <!-- end body should be at end of page -->\n";
        htmltext += " </html><!-- end html should be at end of page -->\n";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
 
      if (myval == 21) {
// this is much easier
var pastetest= ` 
    <li class="photobooth-comment">
       <span class="username">
          <a href="#">You</a>:
       </span>
       <span class="comment-text">
          $text
       </span> 
       @<span class="comment-time">
          2d
       </span> ago <h1>Hello</h1>
    </li>
`;
// this is much easier

        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), pastetest);
      }
      if (myval == 22) {
        //https://wtools.io/html-to-javascript-converter
        var variable = '\n' +
          '<!DOCTYPE html>\n' +
          '<html>\n' +
          '<head>\n' +
          '<style>\n' +
          '/* unvisited link */\n' +
          'a:link {\n' +
          '  color: red;\n' +
          '}\n' +
          '\n' +
          '/* visited link */\n' +
          'a:visited {\n' +
          '  color: green;\n' +
          '}\n' +
          '\n' +
          '/* mouse over link */\n' +
          'a:hover {\n' +
          '  color: hotpink;\n' +
          '}\n' +
          '\n' +
          '/* selected link */\n' +
          'a:active {\n' +
          '  color: blue;\n' +
          '}\n' +
          '</style>\n' +
          '</head>\n' +
          '<body>\n' +
          '\n' +
          '<h2>Styling a link depending on state</h2>\n' +
          '\n' +
          '<p><b><a href="https://www.w3schools.com/css/tryit.asp?filename=trycss_link" target="_blank">https://www.w3schools.com/css/tryit.asp?filename=trycss_link</a></b></p>\n' +
          '<p><b>Note:</b> a:hover MUST come after a:link and a:visited in the CSS definition in order to be effective.</p>\n' +
          '<p><b>Note:</b> a:active MUST come after a:hover in the CSS definition in order to be effective.</p>\n' +
          '\n' +
          '</body>\n' +
          '</html>\n' +
          '\n' +
          '\n' +
          '\n';
        htmltext = variable;
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 23) {
        htmltext = "use pretty button<br>\n<style>.mydivouter{position:relative;}.mydivoverlap{position: relative;z-index: 1;}.mybuttonoverlap{position: absolute;z-index: 2;top: -14px;display: none;left: 50px;}.mybuttonoverlap2{position: absolute;z-index: 1;top: 14px;display: none;left: 50px;}.mydivouter:hover .mybuttonoverlap{display:block;}.mydivouter:hover .mybuttonoverlap2{display:block;}</style>buttons popup test on hover for jumpscroll<br>\n<br><br>\n<div class=\"mydivouter\">\n&nbsp;line 33\n<button type=\"button\" title=\"scrollup\nto previous marked line\" class=\"mybuttonoverlap btn btn-info\">&#11165;</button>\n<button type=\"button\" title=\"scrolldown\nto next marked line\" class=\"mybuttonoverlap2 btn btn-info\">&#11167;</button>\n</div>\n<br><b>\n<br><br><br>\n<iframe src=\"https://plnkr.co/plunk/26pHZDFjoE17QrCz\"width=\"100%\" height=\"600\"></iframe>\n\<!-- https://tutorialdeep.com/knowhow/display-button-on-hover-html-css/ -->";

        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 24) {
        htmltext = " \n";
        htmltext += " \n";
        htmltext += " <iframe width=\"100%\" height=\"100%\" src=\"https://plnkr.co/plunk/vQj5gFfndyrfyjvR\"></iframe>\n"; // morepastes
        htmltext += " \n";
        htmltext += " \n";
        htmltext += " \n";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 25) {
        //https://wtools.io/html-to-javascript-converter
        var variable = `
        <h1>
        coding challenge?>br>
        make it an old fashion <br>
        time switch relais clock<br>
        add quarter points on 2circles, 12 hour each<br>
        hour hand ponts to activated AM/PM circle point<br>
        lost me or not?
        </h1>
        https://nl.rs-online.com/web/p/time-switches/3498680<br>
<br>
<canvas id="canvas" width="400" height="400"style="background-color:#333"></canvas>

<script>
  var canvas = document.getElementById("canvas"); var ctx = canvas.getContext("2d"); var radius = canvas.height / 2; ctx.translate(radius, radius); radius = radius * 0.90;
  setInterval(drawClock, 1000);
  function drawClock() {
    drawFace(ctx, radius);
    drawNumbers(ctx, radius);
    drawTime(ctx, radius);
  }
  function drawFace(ctx, radius) {
    var grad;
    ctx.beginPath();
    ctx.arc(0, 0, radius, 0, 2*Math.PI);
    ctx.fillStyle = 'white';
    ctx.fill();
    grad = ctx.createRadialGradient(0, 0, radius*0.95, 0, 0, radius*1.05);
    grad.addColorStop(0, '#333');
    grad.addColorStop(0.5, 'white');
    grad.addColorStop(1, '#333');
    ctx.strokeStyle = grad;
    ctx.lineWidth = radius*0.1;
    ctx.stroke();
    ctx.beginPath();
    ctx.arc(0, 0, radius*0.1, 0, 2*Math.PI);
    ctx.fillStyle = '#333';
    ctx.fill();
  }
  function drawNumbers(ctx, radius) {
    var ang;
    var num;
    ctx.font = radius*0.15 + "px arial";
    ctx.textBaseline = "middle";
    ctx.textAlign = "center";
    for (num = 1;
      num < 13;
      num++) {
      ang = num * Math.PI / 6;
      ctx.rotate(ang);
      ctx.translate(0, -radius*0.85);
      ctx.rotate(-ang);
      ctx.fillText(num.toString(), 0, 0);
      ctx.rotate(ang);
      ctx.translate(0, radius*0.85);
      ctx.rotate(-ang);
    }}
  function drawTime(ctx, radius) {
    var now = new Date();
    var hour = now.getHours();
    var minute = now.getMinutes();
    var second = now.getSeconds();
    //hour
    hour = hour%12;
    hour = (hour*Math.PI/6)+ (minute*Math.PI/(6*60))+ (second*Math.PI/(360*60));
    drawHand(ctx, hour, radius*0.5, radius*0.07);
    //minute
    minute = (minute*Math.PI/30)+(second*Math.PI/(30*60));
    drawHand(ctx, minute, radius*0.8, radius*0.07);
    // second
    second = (second*Math.PI/30);
    drawHand(ctx, second, radius*0.9, radius*0.02);
  }
  function drawHand(ctx, pos, length, width) {
    ctx.beginPath();
    ctx.lineWidth = width;
    ctx.lineCap = "round";
    ctx.moveTo(0, 0);
    ctx.rotate(pos);
    ctx.lineTo(0, -length);
    ctx.stroke();
    ctx.rotate(-pos);
  }
<\/script>
<br>
 <center><small>
 Electric Storm<br>
 <a href="http://plnkr.co/edit/ZEkhoGgs4ntDZzT0" target="_blank">http://plnkr.co/edit/ZEkhoGgs4ntDZzT0</a><br>
 <br>
 <iframe src="https://plnkr.co/plunk/SELZ9E6NfqEugsLJ" width="100%" height="600"></iframe
 </center>

         `;
        htmltext = variable;
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 26) {
        //https://wtools.io/html-to-javascript-converter
        var variable = '' +
          '<h1><span id="Clock">this text will be replaced by the clock</spanp></h1>\n		' +
          '\n<!--\n https://codepen.io/ldijkman/pen/dymRoeR \n use button pretty? \n and try button fold / unfold? \n-->\n\n' +
          '<script>\n' +
          '' +
          'function updateClock() {\n' +
          'let time = new Date(); \n' +
          'let hours =  time.getHours() ;\n ' +
          'let minutes = time.getMinutes();\nif (minutes<=9){minutes="0"+minutes;}\n' +
          'let seconds = time.getSeconds();\nif (seconds<=9){seconds="0"+seconds;} \n' +
          'this.document.getElementById("Clock").innerHTML = hours+":"+minutes+":"+seconds; \n' +
          '' +
          'setTimeout(updateClock, 1000);\n' +
          '' +
          '} \n' +
          'updateClock(); \n' +
          '// setInterval(updateClock, 1000);\n' +
          '<\/script>\n' +
          '';
        htmltext = variable;
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 27) {
        htmltext = "mouse drag resize editor preview \n";
        htmltext += " \n";
        htmltext += "https://plnkr.co/edit/7zSWRvsXITtckVxV \n";
        htmltext += " <iframe width=\"100%\" height=\"100%\" src=\"https://plnkr.co/edit/7zSWRvsXITtckVxV\"></iframe>\n"; // morepastes
        htmltext += " \n";
        htmltext += " \n";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 28) {
        htmltext = "<!DOCTYPE HTML> \n";
        htmltext += "<html> <!-- start and end document--> \n";
        htmltext += "<head>\n";
        htmltext += "<title> titel of the page </title>\n";
        htmltext += "<style>/* style css shoudl be in the head */\n";
        htmltext += "body{\n";
        htmltext += "  background-color: grey;\n";
        htmltext += "  color: rgb(234,245,19);\n";
        htmltext += "}\n";
        htmltext += "</style>\n";
        htmltext += "</head><!-- end head start body -->\n";
        htmltext += "<body><!-- end head start body -->\n";
 htmltext += "       Please Free Electra<br>\n";
                                          
 htmltext += "<h1>Free Electra ?!</h1>\n";
 
 htmltext += "  Ask developer@githubsupport.com to Free Electra ?!<br>\n<br>\n";
        htmltext += " <a href=\"https://ldijkman.github.io/Electra\" targt=\"Hey_Electra\">https://ldijkman.github.io/Electra</a><br>\n";
       
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 29) {

htmltext = " <script>\n";
htmltext += " /* echo mouse position html elements name on console */\n";
htmltext += "function findElements(e) {\n";
htmltext += "var els = document.elementsFromPoint(e.clientX, e.clientY);\n";
htmltext += "\n";
htmltext += " // do cool stuff with els\n";
htmltext += " console.log(els);\n";
htmltext += "\n";
htmltext += " return;\n";
htmltext += "}\n";
htmltext += "\n";
htmltext += "document.addEventListener(\"mousemove\", findElements);\n";
htmltext += "\n";
htmltext += "<\/script>\n";
htmltext += "<input type=\"color\" id=\"idname\" class=\"classname\" value=\"rgb(80,255,0)\">\n<br>\n<br>\n<h1 id=\"h1_id_name\" class=\"h1_class_name\">hi</h1>";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 30) {
        let code = "";
        code += '\n';
        code += '\n';
        code += '<script>';
        code += 'function brCheck(data)';
        code += '{';
        code += '}';
        code += '';
        code += 'function scriptPHP(data){';
        code += 'brCheck(data);';
        code += 'for (i=0; i<dataArr.length; i++){';
        code += 'data.value+= (i==0) ? "<?php\\necho " : "echo "';
        code += 'data.value+= "\\"" + unescape(dataArr[i]); ';
        code += 'data.value+= (i!=dataArr.length-1) ? "\\\\n\\"; \\n" : "\\\\n\\";\\n"';
        code += '}';
        code += 'data.value+="\\?>"';
        code += '}';
        code += '</script\>';
        code += '\n';
        code += '<style type="text/css">\n';
        code += '<!--\n';
        code += '.input1 {\n';
        code += '	background-color: #ffffff;\n';
        code += '	font-family: Verdana, Arial, Helvetica, sans-serif;\n';
        code += '	font-size: 11px;\n';
        code += '	color: #000000;\n';
        code += '	height: 300px;\n';
        code += '	width: 610px;\n';
        code += '	overflow: auto;\n';
        code += '}\n';
        code += 'body {\n';
        code += '	background-color: #ffffff;\n';
        code += '	overflow: hidden;\n';
        code += '}\n';
        code += '.input2 {\n';
        code += '	font-family: Verdana, Arial, Helvetica, sans-serif;\n';
        code += '	font-size: 12px;\n';
        code += '	color: #FFFFFF;\n';
        code += '	background-color: #005782;\n';
        code += '}\n';
        code += '.borders {\n';
        code += '	border: 1px outset #00406A;\n';
        code += '}\n';
        code += 'a {\n';
        code += '	font-family: Verdana, Arial, Helvetica, sans-serif;\n';
        code += '	font-size: 11px;\n';
        code += '	color: #FFFFFF;\n';
        code += '	text-decoration: none;\n';
        code += '}\n';
        code += 'a:hover {\n';
        code += '	color: #FFFF99;\n';
        code += '}\n';
        code += '-->\n';
        code += '</style>\n';
        code += '</head>\n';
        code += '<body>\n';
        code += '\n';
        code += '<script src="placeholders.min.js"><\/script>\n';
        code += '\n';
        code += '<form name="doc" action="">\n';
        code += '<table width="100" border="0" align="center" cellpadding="3" cellspacing="0" class="javascript_change_case">\n';
        code += '  <tr>\n';
        code += '\t<td colspan="2" align="center"><input name="button" type="button" class="button" onClick="scriptPHP(document.doc.tx)" value="HTML -> PHP">\n';
        code += '\t  <input name="button2" type="button" class="button" onClick="scriptJS(document.doc.tx)" value="HTML -> JavaScript">\n';
        code += '\t  <input name="button2" type="button" class="button" onClick="scriptASP(document.doc.tx)" value="HTML -> ASP">\n';
        code += '\t  <input name="reset" type="reset" class="button" value="Reset" onClick="document.doc.tx.focus()">\n';
        code += '\t  <input name="button2" type="button" class="button" onClick="copyF(document.doc.tx)" value="Select All">\n';
        code += '\n';
        code += '	  <input name="button2" type="button" class="button" onClick="document.doc.tx.value=\'\\n  Copyright (C) 2004 by 2M.Studio Michael Weidemann\\n\\n  You are free to distribute and modify this file, as long as you\\n  do not remove this copyright notice and clearly label modified\\n  versions as being modified.\\n\\n  This software has NO WARRANTY.  Use it at your own risk.\\n  Original location: http://www.2mstudio.de\'" value="Info"></td>\n';
        code += '\t</tr>\n';
        code += '  <tr>\n';
        code += '\t<td colspan="2"> <textarea name="tx" cols="110" class="input1" rows="2" placeholder="Type or paste your content here.\n';
        code += '\n';
        code += 'Privacy of Data: Text-Filter.com ! Doesn\'t save or share your Text/Data. This tool is built-with and functions-in Client Side JavaScripting, so only your computer will see or process your data\n';
        code += 'input/output."></textarea></td>\n';
        code += '\t</tr>\n';
        code += '  <tr>\n';
        code += '\t<td width="395"><a href="http://www.2mstudio.de" target="_blank">&copy; 2004 by 2M.Studio M.Weidemann</a></td>\n';
        code += '\n';
        code += '  </tr>\n';
        code += '</table>\n';
        code += '</form>\n';
        code += '\n';
        code += '</body>\n';
        code += '</html>\n';
        htmltext = code;
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      ace.edit("editor").focus();
      document.getElementById("myList").options[0].selected = true;
    }
 </script>











          // move paste to javascript window
              function paste() {
      var myval = document.getElementById("myList").value;
      var htmltext;
      //console.log(myval);
      if (myval == 1) {
        //    /* */ or <!-- -->
        // test some commands
        ace.edit("editor").execCommand("toggleBlockComment");
        // editor.execCommand("showKeyboardShortcuts");
        //htmltext="<!--     -->";
        //ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
        //console.log(ace.edit("editor").getCursorPosition());
        //console.log(ace.edit("editor").selection.getCursor().column);
        //console.log(ace.edit("editor").selection.getCursor().row);
        //console.log(ace.edit("editor").selection.getCursor().column-6);
        //move cursor rom end of line  inside the comment part of paste
        //ace.edit('editor').gotoLine(ace.edit("editor").selection.getCursor().row+1,ace.edit("editor").selection.getCursor().column-6);
      }

      if (myval == 2) {
 var pastetext=`
 <!DOCTYPE html>
 <html>
 <head>
 <title>  </title>
 <style>
 body{
   background-color:orange;
   color:yellow;
 }
 </style>
 </head>
 <body>
 <center>
 <h1>Hello</h1>
 </center>
 plnkr.co/edit/ZEkhoGgs4ntDZzT0
 </body>
 </html>
        `;
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), pastetext);
      }
      if (myval == 3) {
        htmltext = "<img src=\"https://raw.githubusercontent.com/ldijkman/Electra/main/touch_electra.gif\"><br>\n";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 4) {
        htmltext = "<a href=\"http://ldijkman.github.io/Electra\" target=\"_blank\">Electra</a><br>";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 5) {
        htmltext = "<script type=\"text/javascript\" src=\"\"></script\>\n";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 6) {
        htmltext = "&nbsp;";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 7) {
        htmltext = "&emsp;";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 8) {
        htmltext = "<p align=\"right\">Right align content</p>";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 9) {
      htmltext = `
<iframe id="" align="left" width="500" height="320" src="https://www.youtube.com/embed/5uapPPC8eQY" style="border:none; -ms-transform: scale(1, 1); transform: scale(1, 1)" scrolling="no">
</iframe>
<br>
<br>
<h1>latest video Electric Storm</h1>
<br>
<iframe width="697" height="392" src="https://www.youtube.com/embed/eC0tJmIl_lY" title="Ace Editor Preview   WYSIWYG  Electric Storm" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen>
</iframe><br>
<br>
 <center><small>
 Electric Storm<br>
 <a href="http://plnkr.co/edit/ZEkhoGgs4ntDZzT0" target="_blank">http://plnkr.co/edit/ZEkhoGgs4ntDZzT0</a><br>
 <br>
 </center>
      `;


        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 10) {
        htmltext = "<meta http-equiv=\"Refresh\" content=\"10\">\n";
        htmltext += "<!-- does not work nice in preview editor, reloads the page in 10 seconds -->\n";
        htmltext += "<!-- reload to another URL -->\n";
        htmltext += "<!-- <meta http-equiv=\"refresh\" content=\"30; URL=https://ldijkman.github.io/Electra/\"> -->\n";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 11) {
        htmltext = "<table width=\"100%\" border=\"1\" cellspacing=\"5\" summary=\"bkj\">\n";
        htmltext += "<tr>\n";
        htmltext += "<td style=\"text-align:center;\">1</td>\n";
        htmltext += "<td>2</td>\n";
        htmltext += "<td>3</td>\n";
        htmltext += "</tr>\n";
        htmltext += "<tr>\n";
        htmltext += "<td>4</td>\n";
        htmltext += "<td>5</td>\n";
        htmltext += "<td>6</td>\n";
        htmltext += "</tr>\n";
        htmltext += "</table>\n";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 12) {
        htmltext = "<p>A normal horizontal line:</p>\n";
        htmltext += "<hr>\n";
        htmltext += "<p>With CSS:</p>\n";
        htmltext += "<hr style=\"height:10px; border-width:5; border-color:rgb(17,26,158); background-color:rgb(30,212,116); width:75%;\">\n";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 13) {
        htmltext = "<h0>h0 text</h0>\n";
        htmltext += "<h1>h1 text</h1>\n";
        htmltext += "<h2>h2 text</h2>\n";
        htmltext += "<h3>h3 text</h3>\n";
        htmltext += "<h4>h4 text</h4>\n";
        htmltext += "<h5>h5 text</h5>\n";
        htmltext += "<h6>h6 text</h6>\n";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 14) {
        htmltext = "<p style=\"font-family:Courier; color:rgb(223,15,15); font-size: 20px;\">This text has the font Courier, is rgb(223,15,15), and 20px.</p>\n";
        htmltext += "<!-- https://www.w3schools.com/cssref/css_websafe_fonts.asp -->";
        htmltext += "<!--\nArial (sans-serif)\nVerdana (sans-serif)\nHelvetica (sans-serif)\nTahoma (sans-serif)\nTrebuchet MS (sans-serif)\nTimes New Roman (serif)\nGeorgia (serif)\nGaramond (serif)\nCourier New (monospace)\nBrush Script MT (cursive) \n-->\n";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 15) {
        htmltext = "<link href='https://fonts.googleapis.com/css?family=Sofia' rel='stylesheet'>\n";
        htmltext += "<p style=\"font-family: 'Sofia';font-size: 22px;\">Lorem ipsum dolor sit amet, consectetuer adipiscing elit.</p>\n";
        htmltext += "<!-- https://developers.google.com/fonts/docs/getting_started -->\n";
        htmltext += "<!-- https://www.w3schools.com/css/css_font_google.asp -->";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 16) {
        htmltext = "<link rel=\"stylesheet\" href=\"https://fonts.googleapis.com/css?family=Sofia&effect=fire\">\n";
        htmltext += "<font size=\"77px\" style=\"font-family: \"Sofia\", sans-serif; font-size: 30px;\" class=\"font-effect-fire\">Russia on Fire</font>\n";
        htmltext += "<p style=\"font-family: \"Sofia\", sans-serif; font-size: 30px;\" class=\"font-effect-fire\">Burn MF burn.</p>\n";
        htmltext += "<p style=\"font-family: \"Sofia\", sans-serif; font-size: 30px;\" class=\"font-effect-fire\">123</p>\n";
        htmltext += "<!-- https://www.w3schools.com/css/css_font_google.asp -->\n";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 17) {
        htmltext = "<style>/* style css shoudl be in the head */\n";
        htmltext += "body{\n";
        htmltext += "background-color:rgb(13,13,12);\n";
        htmltext += "color:yellow;\n";
        htmltext += "}\n";
        htmltext += "</style>\n";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 18) {
        // test for mark linenumbers and easy scroll to edit positions
        htmltext = "<!-- mark/unmark gutter linenumbers with mouseclick -->\n";
        htmltext += "<!-- want to make a scroll up down button for easy scroll -->\n";
        htmltext += "<!-- to marked line numbers -->\n";
        htmltext += "<!-- for easy code edit jumping -->\n";
        htmltext += "<!-- for now jump to line 20 -->\n";
        htmltext += "<!-- JumpSrroll to Marked linenumbers by mouseclick Electrric Storm -->\n";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
        ace.edit("editor").scrollToLine(20, true, true, );
        ace.edit("editor").gotoLine(20, 0, true);
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 19) {
        htmltext = "<style>\na:hover {\n background-color: yellow;\n}\n</style>\n\n";
        htmltext += "<h1>\n<a href=\"https://codepen.io/ldijkman/pen/dymRoeR\" target=\"new1\">linktext one</a><br><br>\n<a href=\"https://codepen.io/ldijkman/pen/dymRoeR\" target=\"new2\">linktext two</a>\n</h1>";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
      if (myval == 20) {
        htmltext = "<!DOCTYPE HTML> \n";
        htmltext += "<html> <!-- start and end document--> \n";
        htmltext += "<head>\n";
        htmltext += "<title> titel of the page </title>\n";
        htmltext += "<style>/* style css shoudl be in the head */\n";
        htmltext += "body{\n";
        htmltext += "  background-color: rgb(47,52,107);\n";
        htmltext += "  color: rgb(234,245,19);\n";
        htmltext += "}\n";
        htmltext += "</style>\n";
        htmltext += "</head><!-- end head start body -->\n";
        htmltext += "<body><!-- end head start body -->\n";
        htmltext += "<h1>Hello h1 text</h1>\n";
        htmltext += "<h2>h2 text</h2>\n";
        htmltext += "<h3>h3 text</h3>\n";
        htmltext += "<h4>h4 text</h4>\n";
        htmltext += "<h5>h5 text</h5>\n";
        htmltext += "<h6>h6 text</h6>\n";
        htmltext += "<hr> hr is a horizontal line ruler <br>\n";
        htmltext += "<center> center text </center> \n";
        htmltext += "<p> Paragraph 1 </p>\n";
        htmltext += "<p> Paragraph 2 </p>\n";
        htmltext += "<p> Paragraph 3</p>\n";
        htmltext += "br break the line to new line<br>\n";
        htmltext += "&nbsp; is a space <br>\n";
        htmltext += "<strike> strike trough text </strike><br>\n";
        htmltext += "<b> bold text </b><bbr>\n";
        htmltext += "<i> italic text</i><br>\n";
        htmltext += "<u>underline text</u><br>\n";
        htmltext += "<li> list item </li><br>\n";
        htmltext += "<blockquote>blockquote</blockquote><br>\n";
        htmltext += " </body> <!-- end body should be at end of page -->\n";
        htmltext += " </html><!-- end html should be at end of page -->\n";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }
 
      if (myval == 21) {

var pastetest; /*<<<EOF 
    <li class="photobooth-comment">
       <span class="username">
          <a href="#">You</a>:
       </span>
       <span class="comment-text">
          $text
       </span> 
       @<span class="comment-time">
          2d
       </span> ago <h1>Hello</h1>
    </li>
EOF*/

// note the script tag here is hardcoded as the FIRST tag 

pastetest = document.currentScript.innerHTML.split("EOF")[1];

        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), pastetest);
      }