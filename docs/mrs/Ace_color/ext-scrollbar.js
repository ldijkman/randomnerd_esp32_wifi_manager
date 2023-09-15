/*
https://github.com/ukandrewc/Ace-Scrollbars/tree/master
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
					ht += "<div class='ace_map-item' style='top:" + (r.start.row * rScale) + "px'></div>"
					lr = r.start.row
				}
			}
		}
		mc.innerHTML = ht
		mr.style.top = e.getCursorPosition().row * rScale + "px"
	}

	// Vertical
	let rScale = 1
	let vScale = 1
	let vStart = -1

	let vs = sc[0]
	let tv = document.getElementById("ace_bar-v")

	vs.addEventListener("scroll", function () {
		tv.style.top = vs.scrollTop * vScale + "px"
	})

	// Drag events
	tv.addEventListener("pointerdown", function (e) {
		tv.setPointerCapture(e.pointerId)
		vStart = e.clientY
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
		vs.scrollTop = e.clientY / vScale
	})

	// Horizontal
	let hScale = 1
	let hStart = -1

	let hs = sc[1]
	let th = document.getElementById("ace_bar-h")

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

	resizeScroll = function () {
		vScale = vs.clientHeight / vs.scrollHeight
		if (vs.clientHeight) {
			tv.style.height = (vs.clientHeight * vScale) + "px"
			showScroll(tv, true)
		}
		else {
			showScroll(tv, false)
		}

		hScale = hs.clientWidth / hs.scrollWidth
		if (hs.clientWidth) {
			th.style.width = (hs.clientWidth * hScale) + "px"
			th.style.left = (hs.scrollLeft * hScale) + gWidth + "px"
			showScroll(th, true)
		}
		else {
			showScroll(th, false)
		}

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



	resizeScroll()
}
