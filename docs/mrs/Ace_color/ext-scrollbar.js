/*
https://github.com/ukandrewc/Ace-Scrollbars/tree/master

changes
https://plnkr.co/edit/Digj5Fw7D6hxaTU4
my editor does not start at mousepos y zero
so i treid to make an offset for that

still a problem with scrollbar viewport on fontsize
only seems to work ok at fontsize 12

*/

function AceScrollbars(e) {

	// Add CSS scrollbars
	e.container.insertAdjacentHTML("beforeend", "<div id='ace_pre-v' class='ace_scroll-v'></div><div id='ace_bar-v' class='ace_scroll-v ace_thumb-v'></div>")
	e.container.insertAdjacentHTML("beforeend", "<div id='ace_pre-h' class='ace_scroll-h'></div><div id='ace_bar-h' class='ace_scroll-h ace_thumb-h'></div>")
	e.container.insertAdjacentHTML("beforeend", "<div id='ace_map-row' class='ace_map-row'></div>")
	e.container.insertAdjacentHTML("beforeend", "<div id='ace_map'></div>")

	// Ace scrollbars
	let gWidth = 34
	let sc = document.getElementsByClassName("ace_scrollbar")

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
	let mr = document.getElementById("ace_map-row")
	let mc = document.getElementById("ace_map")

	let h = 0
	e.on("changeSelection", function () {
		clearTimeout(h)
		h = setTimeout(showMapItems, 250)
	})

	///////////////////////////////////////////////////////////////////////////
// arduino alike map function == Re-maps a number from one range to another. 
// https://www.arduino.cc/reference/en/language/functions/math/map/ 
// https://stackoverflow.com/questions/5649803/remap-or-map-function-in-javascript
// scale range 1 into range2 bar range to 0 to 1440 minute range  
// or 
// scale a minutevalue in range 0 to 1440 minutes to 0% to 100%,  used for left and width of timeslot divs
///////////////////////////////////////////////////////////////////////////////
function map_range(value, low1, high1, low2, high2) {
    return (low2 + (high2 - low2) * (value - low1) / (high1 - low1)).toFixed(3);   // to 3 decimals, Math.round did not scale right
}


	showMapItems = function () {
		let ht = ""
		let tx = e.getCopyText()
		if (tx != "") {
			let op = e.getLastSearchOptions()
			op.needle = e.getCopyText()
			e.$search.setOptions(op)
			let lr = -1
			for (r of e.$search.findAll(e.session)) {
				if (r.start.row != lr) {
					ht += "<div class='ace_map-item' style='top:" +  (map_range(r.start.row ,0,editor.session.getLength(), 0,100)) + "%'></div>"
					// luberth thinks, i do not know maybe better in % no px
					console.log("rScale",rScale);
					lr = r.start.row
				}
			}
		}
		mc.innerHTML = ht
		mr.style.top = map_range(e.getCursorPosition().row,0,editor.session.getLength(), 0,100)+"%"
		console.log("rScale2",rScale);
	}

	// Vertical
	let rScale = 1
		
	let vScale = 1
	let vStart = -1

	let vs = sc[0]
	let tv = document.getElementById("ace_bar-v")    // tv is the gray view on scrollbar, should match the editor view position

	vs.addEventListener("scroll", function (e) {//think it needes an offset here if editor does not start at top 0 of document
		tv.style.top = (vs.scrollTop-document.getElementById("editor").offsetTop) * vScale + "px"
	//tv.style.top = (vs.scrollTop-e.offsetTop) * vScale + "px"

	})

	// Drag events
	tv.addEventListener("pointerdown", function (e) {
		tv.setPointerCapture(e.pointerId)
		vStart = e.clientY
    //console.log("e.clientY",e.clientY);
    //console.log("mc.offsetTop+'px'",mc.offsetTop);
    console.log("offsetTop",document.getElementById("editor").offsetTop);
    
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
     vs.scrollTop = (e.clientY-document.getElementById("editor").offsetTop) / vScale
	   //vs.scrollTop = (e.clientY-e.offsetTop) / vScale

	})

	// Horizontal
	let hScale = 1
	let hStart = -1

	let hs = sc[1]
	let th = document.getElementById("ace_bar-h")
/*
	hs.addEventListener("scroll", function () {
		th.style.left = (hs.scrollLeft * hScale) + gWidth + "px"
	})

	// Drag events
	th.addEventListener("pointerdown", function (e) {
		th.setPointerCapture(e.pointerId)
		hStart = e.clientX
	})

	th.addEventListener("pointermove", function (e) {
		if (hStart != -1) {
			hs.scrollLeft += (e.clientX - hStart) / hScale
			hStart = e.clientX
		}
	})

	th.addEventListener("pointerup", function (e) {
		th.releasePointerCapture(e.pointerId)
		hStart = -1
	})

	th.previousElementSibling.addEventListener("mousedown", function (e) {
		hs.scrollLeft = e.clientX / hScale
	})
*/
	resizeScroll = function () {
		vScale = vs.clientHeight / vs.scrollHeight
		if (vs.clientHeight) {
			tv.style.height = (vs.clientHeight * vScale) + "px"
			showScroll(tv, true)
		}
		else {
			showScroll(tv, false)
		}
/*
		hScale = hs.clientWidth / hs.scrollWidth 
		if (hs.clientWidth) {
			th.style.width = (hs.clientWidth * hScale) + "px"
			th.style.left = (hs.scrollLeft * hScale) + gWidth + "px"
			showScroll(th, true)
		}
		else {
			showScroll(th, false)
		}
*/
		rScale = e.renderer.lineHeight * vScale
		console.log("e.renderer.lineHeight",e.renderer.lineHeight);
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
