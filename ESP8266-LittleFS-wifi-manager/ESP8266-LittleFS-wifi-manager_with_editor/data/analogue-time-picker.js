(function webpackUniversalModuleDefinition(root, factory) {
	if(typeof exports === 'object' && typeof module === 'object')
		module.exports = factory();
	else if(typeof define === 'function' && define.amd)
		define([], factory);
	else {
		var a = factory();
		for(var i in a) (typeof exports === 'object' ? exports : root)[i] = a[i];
	}
})(window, function() {
return /******/ (function(modules) { // webpackBootstrap
/******/ 	// The module cache
/******/ 	var installedModules = {};
/******/
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/
/******/ 		// Check if module is in cache
/******/ 		if(installedModules[moduleId]) {
/******/ 			return installedModules[moduleId].exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = installedModules[moduleId] = {
/******/ 			i: moduleId,
/******/ 			l: false,
/******/ 			exports: {}
/******/ 		};
/******/
/******/ 		// Execute the module function
/******/ 		modules[moduleId].call(module.exports, module, module.exports, __webpack_require__);
/******/
/******/ 		// Flag the module as loaded
/******/ 		module.l = true;
/******/
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/
/******/
/******/ 	// expose the modules object (__webpack_modules__)
/******/ 	__webpack_require__.m = modules;
/******/
/******/ 	// expose the module cache
/******/ 	__webpack_require__.c = installedModules;
/******/
/******/ 	// define getter function for harmony exports
/******/ 	__webpack_require__.d = function(exports, name, getter) {
/******/ 		if(!__webpack_require__.o(exports, name)) {
/******/ 			Object.defineProperty(exports, name, {
/******/ 				configurable: false,
/******/ 				enumerable: true,
/******/ 				get: getter
/******/ 			});
/******/ 		}
/******/ 	};
/******/
/******/ 	// define __esModule on exports
/******/ 	__webpack_require__.r = function(exports) {
/******/ 		Object.defineProperty(exports, '__esModule', { value: true });
/******/ 	};
/******/
/******/ 	// getDefaultExport function for compatibility with non-harmony modules
/******/ 	__webpack_require__.n = function(module) {
/******/ 		var getter = module && module.__esModule ?
/******/ 			function getDefault() { return module['default']; } :
/******/ 			function getModuleExports() { return module; };
/******/ 		__webpack_require__.d(getter, 'a', getter);
/******/ 		return getter;
/******/ 	};
/******/
/******/ 	// Object.prototype.hasOwnProperty.call
/******/ 	__webpack_require__.o = function(object, property) { return Object.prototype.hasOwnProperty.call(object, property); };
/******/
/******/ 	// __webpack_public_path__
/******/ 	__webpack_require__.p = "";
/******/
/******/
/******/ 	// Load entry module and return exports
/******/ 	return __webpack_require__(__webpack_require__.s = 0);
/******/ })
/************************************************************************/
/******/ ([
/* 0 */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);

// CONCATENATED MODULE: ./src/utils/utils.ts
/** Add an event listener to an element and return a function which will dispose of the listener */
function registerEvent(element, event, fun) {
    function f() { return fun.apply(this, arguments); }
    element.addEventListener(event, f);
    var removed = false;
    return function () {
        if (removed)
            return;
        removed = true;
        element.removeEventListener(event, f);
    };
}
/** Add an event listener to an element and return a function which will dispose of the listener */
function registerMouseEvent(element, event, fun) {
    return registerEvent(element, event, fun);
}
/** Add an event listener to an element and return a function which will dispose of the listener */
function registerKeyEvent(element, event, fun) {
    return registerEvent(element, event, fun);
}
/** Add an event listener to an element and return a function which will dispose of the listener */
function registerTouchEvent(element, event, fun) {
    return registerEvent(element, event, fun);
}


// CONCATENATED MODULE: ./src/components/gestureTracker.ts

/** Track the mouse position over the entire screen and report back */
var gestureTracker_GestureTracker = /** @class */ (function () {
    function GestureTracker(moveEvents, finishEvents) {
        var _this = this;
        this._disposables = [];
        this._onFinished = [];
        this._onMove = [];
        var me = moveEvents
            .map(function (x) { return registerEvent(document, x, function (e) { return _this.move(e); }); });
        var fe = finishEvents
            .map(function (x) { return registerEvent(document, x, function (e) { return _this.finish(); }); });
        this._disposables = me.concat(fe);
    }
    GestureTracker.prototype.onFinished = function (callback) {
        this._onFinished.push(callback);
    };
    GestureTracker.prototype.onMove = function (callback) {
        this._onMove.push(callback);
    };
    GestureTracker.prototype.move = function (e) {
        this._onMove
            .slice(0)
            .forEach(function (f) { return f(e); });
    };
    GestureTracker.prototype.finish = function () {
        this._onFinished
            .slice(0)
            .forEach(function (f) { return f(); });
    };
    GestureTracker.prototype.dispose = function () {
        this._onFinished.length = 0;
        this._onMove.length = 0;
        this._disposables
            .splice(0, Number.MAX_VALUE)
            .forEach(function (f) { return f(); });
    };
    return GestureTracker;
}());


// CONCATENATED MODULE: ./src/components/timePicker.ts
var __assign = (undefined && undefined.__assign) || Object.assign || function(t) {
    for (var s, i = 1, n = arguments.length; i < n; i++) {
        s = arguments[i];
        for (var p in s) if (Object.prototype.hasOwnProperty.call(s, p))
            t[p] = s[p];
    }
    return t;
};


/**The time picker component which contains all other components */
var timePicker_TimePicker = /** @class */ (function () {
    function TimePicker(elements, hours, minutes, hand, mode, focusInput) {
        var _this = this;
        this.hours = hours;
        this.minutes = minutes;
        this.hand = hand;
        this._timeChangeCallbacks = [];
        this._okCallbacks = [];
        this._cancelCallbacks = [];
        this.mouseTracker = null;
        this.touchTracker = null;
        this.ok = elements.okButton;
        this.cancel = elements.cancelButton;
        this.clock = elements.clock;
        // register events for when something happens with the "hours"
        this.hours.onNext(function () { return _this.showMinutes(); });
        this.hours.onRenderValuesChanged(function () { return _this.hourChangeOccurred(); });
        this.hours.onInputFocus(function () { return _this.showHours(true); });
        // register events for when something happens with the "minutes"
        this.minutes.onNext(function () { return _this.ok.focus(); });
        this.minutes.onPrevious(function () { return _this.showHours(true); });
        this.minutes.onRenderValuesChanged(function () { return _this.minuteChangeOccurred(); });
        this.minutes.onInputFocus(function () { return _this.showMinutes(); });
        // show hours by default
        this.showHours(focusInput);
        // register dom events on clock face, ok and cancel buttons
        this._createMouseTracker = registerMouseEvent(this.clock, "mousedown", function (e) { return _this.createMouseTracker(e); });
        this._createTouchTracker = registerTouchEvent(this.clock, "touchstart", function (e) { return _this.createTouchTracker(e); });
        this._okPropagation = registerMouseEvent(this.ok, "mousedown", function (e) { return e.stopPropagation(); });
        this._cancelPropagation = registerMouseEvent(this.cancel, "mousedown", function (e) { return e.stopPropagation(); });
        this._ok = registerMouseEvent(this.ok, "click", function () { return _this.okClick(); });
        this._cancel = registerMouseEvent(this.cancel, "click", function () { return _this.cancelClick(); });
        this.setMode(mode);
    }
    /**Add a callback to be fired when the time changes */
    TimePicker.prototype.onTimeChanged = function (callback) {
        this._timeChangeCallbacks.push(callback);
    };
    /**Add a callback to be fired when the user is finished */
    TimePicker.prototype.onOk = function (callback) {
        this._okCallbacks.push(callback);
    };
    /**Add a callback to be fired when the cancels */
    TimePicker.prototype.onCancel = function (callback) {
        this._cancelCallbacks.push(callback);
    };
    /**Set the format to 12h or 24h for the user */
    TimePicker.prototype.setMode = function (mode) {
        switch (mode) {
            case 12:
                this.hours.setTo12Hr();
                break;
            case 24:
                this.hours.setTo24Hr();
                break;
        }
    };
    /** Show the hour hand */
    TimePicker.prototype.showHours = function (focusInput) {
        this.hours.focus(focusInput);
        this.minutes.blur();
        this.hand.setPositon(this.hours.value.angle, this.hours.value.position);
    };
    /**Show the minute hand */
    TimePicker.prototype.showMinutes = function () {
        this.minutes.normalizeAngle(this.hours.value.angle);
        this.minutes.focus();
        this.hours.blur();
        this.hand.setPositon(this.minutes.value.angle, this.minutes.value.position);
    };
    /** Return the current time */
    TimePicker.prototype.getTime = function () {
        return {
            hour: this.hours.value.value,
            minute: this.minutes.value.value
        };
    };
    /** Set the current time */
    TimePicker.prototype.setTime = function (hours, minutes) {
        var timeHasChanged = this._suppressTimeChangeEvents();
        try {
            this.hours.set(hours);
            this.minutes.set(minutes);
        }
        finally {
            timeHasChanged.complete();
        }
    };
    TimePicker.prototype.hourChangeOccurred = function () {
        if (this.hours.getFocused())
            this.hand.setPositon(this.hours.value.angle, this.hours.value.position);
        this.timeChangeOccurred();
    };
    TimePicker.prototype.minuteChangeOccurred = function () {
        if (this.minutes.getFocused())
            this.hand.setPositon(this.minutes.value.angle, this.minutes.value.position);
        this.timeChangeOccurred();
    };
    TimePicker.prototype.timeChangeOccurred = function () {
        var _this = this;
        if (this._timeChangeSuppressed)
            return;
        this._timeChangeCallbacks
            .slice(0)
            .forEach(function (f) { return f(_this.hours.value.value, _this.minutes.value.value); });
    };
    /**Signify that the user is finished */
    TimePicker.prototype.okClick = function () {
        var _this = this;
        this._okCallbacks
            .slice(0)
            .forEach(function (f) { return f(_this.hours.value.value, _this.minutes.value.value); });
    };
    /**Signify that the user has cancelled */
    TimePicker.prototype.cancelClick = function () {
        this._cancelCallbacks
            .slice(0)
            .forEach(function (f) { return f(); });
    };
    /** Specify that the time may change, and to supress change events if it does.
     * When the returned "compltete" function is called, events are re-enabled, and one may be
     * fired immediately if the time has changed while evets were disabled*/
    TimePicker.prototype._suppressTimeChangeEvents = function () {
        var _this = this;
        // if events already suppressed, signify that
        // one more "supressor" is active
        if (this._timeChangeSuppressed) {
            this._timeChangeSuppressed.instance++;
        }
        else {
            this._timeChangeSuppressed = __assign({ instance: 1 }, this.getTime() // TODO: do we need to watch hand angle/position here too?
            );
        }
        ;
        var c = false;
        return {
            complete: function () {
                if (c)
                    return;
                c = true;
                if (!_this._timeChangeSuppressed)
                    return;
                else if (_this._timeChangeSuppressed.instance > 1)
                    _this._timeChangeSuppressed.instance--;
                else {
                    // if time has changed, fire event if necessary
                    var t1 = _this._timeChangeSuppressed;
                    _this._timeChangeSuppressed = null;
                    var t2 = _this.getTime();
                    if (t1.hour != t2.hour || t1.minute != t2.minute) {
                        _this.timeChangeOccurred();
                    }
                }
            }
        };
    };
    /** Create an object to track the mousemove on the entire screen */
    TimePicker.prototype.createMouseTracker = function (e) {
        var _this = this;
        // touch takes precedence over mouse
        if (this.touchTracker)
            return;
        // use this as an opportunity to see if the clock html element has moved
        this.hours.refreshOffsets();
        this.minutes.refreshOffsets();
        // Set the current hours or minutes
        this.setTimeFromPosition(e.clientX, e.clientY);
        // create a new tracker
        if (this.mouseTracker)
            return;
        var mouseTracker = this.mouseTracker = new gestureTracker_GestureTracker(["mousemove"], ["mouseup"]);
        // dispose when mouse released
        mouseTracker.onFinished(function () {
            mouseTracker.dispose();
            if (mouseTracker === _this.mouseTracker)
                _this.mouseTracker = null;
            _this.hours.getFocused() ?
                _this.hours.goNext() :
                _this.minutes.goNext();
        });
        mouseTracker.onMove(function (e) { return _this.setTimeFromPosition(e.clientX, e.clientY); });
    };
    /** Create an object to track the touchmove over the entire screen */
    TimePicker.prototype.createTouchTracker = function (e) {
        var _this = this;
        // touch takes precedence over mouse
        if (this.mouseTracker) {
            this.mouseTracker.dispose();
            this.mouseTracker = null;
        }
        // prevent scrolling
        e.preventDefault();
        // use this as an opportunity to see if the clock html element has moved
        this.hours.refreshOffsets();
        this.minutes.refreshOffsets();
        // Set the current hours or minutes
        if (e.touches.length) {
            this.setTimeFromPosition(e.touches[0].clientX, e.touches[0].clientY);
        }
        // create a new tracker
        if (this.touchTracker)
            return;
        var touchTracker = this.touchTracker = new gestureTracker_GestureTracker(["touchmove"], ["touchend", "touchcancel"]);
        // dispose when touch released
        touchTracker.onFinished(function () {
            touchTracker.dispose();
            if (touchTracker === _this.touchTracker)
                _this.touchTracker = null;
            _this.hours.getFocused() ?
                _this.hours.goNext() :
                _this.minutes.goNext();
        });
        touchTracker.onMove(function (e) {
            // prevent scrolling
            e.preventDefault();
            if (e.touches.length) {
                _this.setTimeFromPosition(e.touches[0].clientX, e.touches[0].clientY);
            }
        });
    };
    TimePicker.prototype.setTimeFromPosition = function (clientX, clientY) {
        this.hours.getFocused() ?
            this.hours.setFromPosition(clientX, clientY) :
            this.minutes.setFromPosition(clientX, clientY);
    };
    TimePicker.prototype.dispose = function () {
        if (this.mouseTracker) {
            this.mouseTracker.dispose();
            this.mouseTracker = null;
        }
        this._timeChangeCallbacks.length = 0;
        this._okCallbacks.length = 0;
        this._cancelCallbacks.length = 0;
        this._createMouseTracker();
        this._createTouchTracker();
        this._okPropagation();
        this._cancelPropagation();
        this._ok();
        this._cancel();
    };
    return TimePicker;
}());


// CONCATENATED MODULE: ./src/utils/angle.ts
var _90 = Math.PI / 2;
var _360 = Math.PI * 2;
/** Get the angle of the left/top co-ordinate from the center of the width.height box */
function getAngle(left, top, width, height) {
    var x = (width / 2) - left;
    var y = (height / 2) - top;
    // tan O = y / x
    var angle = x ?
        Math.atan(y / x) :
        y < 0 ? -_90 : _90;
    if (x < 0) {
        // reflect along vertical axis
        angle = -angle + (2 * (_90 + angle));
    }
    return angle;
}
/** Calculate the smallest difference between 2 angles. e.g. 90° is smaller than 450° */
function getAngleDelta(a1, a2) {
    var diff = a2 - a1;
    while (diff > Math.PI) {
        diff -= _360;
    }
    while (diff < -Math.PI) {
        diff += _360;
    }
    return diff;
}


// CONCATENATED MODULE: ./src/utils/html.ts

/** Get the offset to the window of an element */
function offset(el, prop) {
    var offset = 0;
    while (el instanceof HTMLElement) {
        offset += el[prop];
        if (window.getComputedStyle(el).getPropertyValue("position") === "fixed")
            return offset;
        el = el.offsetParent;
    }
    offset -= (prop === "offsetTop" ? window.pageYOffset : window.pageXOffset);
    return offset;
}
/** Remove the child of an element if the element contains this child */
function removeChildSafe(parent, child) {
    if (child.parentElement === parent)
        parent.removeChild(child);
}
/** Track the number of modals on screen, and the initial overflow of the body element */
var modalInstance = null;
/** Render the given element as a modal, and return a function to close the modal */
function createModal(content) {
    var modal = document.createElement("div");
    modal.className = "atp-modal";
    modal.appendChild(content);
    document.body.appendChild(modal);
    // cache the body overflow
    if (!modalInstance) {
        modalInstance = {
            overflowX: document.body.style.overflowX,
            overflowY: document.body.style.overflowY,
            instance: 1
        };
        document.body.style.overflowX = "hidden";
        document.body.style.overflowY = "hidden";
    }
    else {
        modalInstance.instance++;
    }
    // register close events
    var onClickOrEsc = [];
    // using mouse down as click might fire on mouse up, if mouse down was not on this element
    var disposeOnMouseDown = registerEvent(modal, "mousedown", function (e) {
        if (e.target !== modal)
            return;
        onClickOrEsc.slice(0).forEach(function (f) { return f(); });
    });
    var disposeOnEsc = registerKeyEvent(document, "keydown", function (e) {
        if (e.key !== "Escape")
            return;
        onClickOrEsc.slice(0).forEach(function (f) { return f(); });
    });
    var done = false;
    return {
        /** Add an event lisener to the mask being clicked or the escape key being pressed */
        onClickOrEsc: function (f) { return onClickOrEsc.push(f); },
        /** Remove the modal from the screen */
        dispose: function () {
            if (done)
                return;
            done = true;
            disposeOnMouseDown();
            disposeOnEsc();
            onClickOrEsc.length = 0;
            removeChildSafe(modal, content);
            removeChildSafe(document.body, modal);
            // reset the body overflow if this is the last modal
            if (modalInstance) {
                if (modalInstance.instance > 1) {
                    modalInstance.instance--;
                }
                else {
                    document.body.style.overflowX = modalInstance.overflowX;
                    document.body.style.overflowY = modalInstance.overflowY;
                    modalInstance = null;
                }
            }
        }
    };
}


// CONCATENATED MODULE: ./src/components/numbers.ts
var numbers_assign = (undefined && undefined.__assign) || Object.assign || function(t) {
    for (var s, i = 1, n = arguments.length; i < n; i++) {
        s = arguments[i];
        for (var p in s) if (Object.prototype.hasOwnProperty.call(s, p))
            t[p] = s[p];
    }
    return t;
};

var numbers_360 = Math.PI * 2;
var Position;
(function (Position) {
    Position["near"] = "near";
    Position["far"] = "far";
})(Position || (Position = {}));
function round(x, decimals) {
    return parseFloat(x.toFixed(decimals));
}
function sign(x) {
    if (!x)
        return 0;
    if (x > 0)
        return 1;
    return -1;
}
function compareAngles(x, y) {
    while (x < 0)
        x += numbers_360;
    while (x >= 0)
        x -= numbers_360;
    while (y < 0)
        y += numbers_360;
    while (y >= 0)
        y -= numbers_360;
    return sign(round(x, 5) - round(y, 5));
}
/** Base class for a number value (e.g. hours, minutes) */
var numbers_Numbers = /** @class */ (function () {
    function Numbers(numberInput, elements, value) {
        var _this = this;
        this.numberInput = numberInput;
        this._onInputFocus = [];
        this._onRenderValuesChanged = [];
        this._onValueChanged = [];
        this._onNextCallbacks = [];
        this._onPreviousCallbacks = [];
        this._triggerValue = null;
        this.ignoreCount = 0;
        this.elements = numbers_assign({}, elements, { selectedNumber: null });
        this.refreshOffsets();
        this.set(value);
        this.numberInput.onTimeChanged(function (v) { return _this.numberInputTimeChanged(v); });
        this.numberInput.onNext(function () { return _this.goNext(); });
        this.numberInput.onPrevious(function () { return _this.goPrevious(); });
        this.highlightNumber();
        this.numberInput.onFocus(function () { return _this.focusOnInput(); });
        this.onRenderValuesChanged(function (rv) { return _this.triggerValueChanged(rv.value); });
        // hidden by default. A parent component will need to call focus(...)
        this.blur();
        this.setLabel();
    }
    Numbers.prototype.onInputFocus = function (f) {
        this._onInputFocus.push(f);
    };
    /** Triggers if value, angle or position changes */
    Numbers.prototype.onRenderValuesChanged = function (f) {
        this._onRenderValuesChanged.push(f);
    };
    /** Triggers only if value (e.g hour) changes */
    Numbers.prototype.onValueChanged = function (f) {
        this._onValueChanged.push(f);
    };
    /** Triggers when the component decides it should move on (like tab) */
    Numbers.prototype.onNext = function (f) {
        this._onNextCallbacks.push(f);
    };
    /** Triggers when the component decides it should move back (like shift tab) */
    Numbers.prototype.onPrevious = function (f) {
        this._onPreviousCallbacks.push(f);
    };
    /** Set the label. This is for accessability purposes only */
    Numbers.prototype.setLabel = function () {
        this.elements.label.innerHTML = this.getLabel();
    };
    Numbers.prototype.focusOnInput = function () {
        this._onInputFocus
            .slice(0)
            .forEach(function (f) { return f(); });
    };
    Numbers.prototype.triggerValueChanged = function (value) {
        if (this._triggerValue === value)
            return;
        this._triggerValue = value;
        this._onValueChanged
            .slice(0)
            .forEach(function (f) { return f(value); });
    };
    /** Specify that this component is finished with input (like tab) */
    Numbers.prototype.goNext = function () {
        this._onNextCallbacks
            .slice(0)
            .forEach(function (cb) { return cb(); });
    };
    /** Specify that this component is finished with input (like shift tab) */
    Numbers.prototype.goPrevious = function () {
        this._onPreviousCallbacks
            .slice(0)
            .forEach(function (cb) { return cb(); });
    };
    /** re-calculate the width, height and position of the elements */
    Numbers.prototype.refreshOffsets = function () {
        this.offsetLeft = offset(this.elements.containerElement, "offsetLeft");
        this.offsetTop = offset(this.elements.containerElement, "offsetTop");
        this.width = this.elements.containerElement.offsetWidth;
        this.height = this.elements.containerElement.offsetHeight;
        var fontSize = parseFloat(window.getComputedStyle(this.elements.containerElement).fontSize || "x");
        if (isNaN(fontSize))
            fontSize = parseFloat(window.getComputedStyle(document.body).fontSize || "x");
        this.fontSize = isNaN(fontSize) ? null : fontSize;
    };
    Numbers.prototype.getFocused = function () { return this.focused; };
    /** Set the value based on the mouse position */
    Numbers.prototype.setFromPosition = function (mouseX, mouseY) {
        var v = this.getValuesFromPosition(mouseX - this.offsetLeft, mouseY - this.offsetTop);
        this._set(v);
    };
    /** Set the value */
    Numbers.prototype.set = function (value) {
        var v = this.getValuesFromValue(value);
        this._set(v);
    };
    Numbers.prototype._set = function (value) {
        if (this.value &&
            this.value.value === value.value &&
            !compareAngles(this.value.angle, value.angle) &&
            this.value.position === value.position)
            return;
        this.value = value;
        this.numberInput.set(value.value);
        this.highlightNumber();
        this._onRenderValuesChanged
            .slice(0)
            .forEach(function (f) { return f(value); });
    };
    /** Highlight a number in the clock */
    Numbers.prototype.highlightNumber = function () {
        if (this.elements.selectedNumber) {
            this.elements.selectedNumber.classList.remove("atp-number-selected");
        }
        this.elements.selectedNumber = this.getSelectedNumberElement();
        if (this.elements.selectedNumber)
            this.elements.selectedNumber.classList.add("atp-number-selected");
    };
    Numbers.prototype.getSelectedNumberElement = function () {
        return this.elements.numbers[this.value.value] || null;
    };
    Numbers.prototype.numberInputTimeChanged = function (v) {
        if (!this.ignoreCount)
            this.set(v);
    };
    /** Ignore change events coming from the numberInput property */
    Numbers.prototype.ignoreNumberInputChangeEvent = function () {
        var _this = this;
        this.ignoreCount++;
        var done = false;
        return function () {
            if (done)
                return;
            done = true;
            _this.ignoreCount--;
        };
    };
    /** Focus this component
     * @param {boolean} [focusInput=true] If true, will focus the cursor on the input also
     */
    Numbers.prototype.focus = function (focusInput) {
        if (focusInput === void 0) { focusInput = true; }
        this.elements.containerElement.style.transform = "scale(1)";
        this.elements.containerElement.style.opacity = "1";
        this.focused = true;
        this.numberInput.focus(focusInput);
    };
    /** Blur this component */
    Numbers.prototype.blur = function () {
        this.elements.containerElement.style.transform = "scale(0)";
        this.elements.containerElement.style.opacity = "0";
        this.focused = false;
        this.numberInput.blur();
    };
    /** alter angle so that it is closest to the given angle, e.g. 500deg -> 140deg */
    Numbers.prototype.normalizeAngle = function (angle) {
        var angle1 = angle % numbers_360;
        var angle2 = this.value.angle % numbers_360;
        this.value.angle = angle + angle2 - angle1;
    };
    Numbers.prototype.dispose = function () {
        this._onValueChanged.length = 0;
        this._onPreviousCallbacks.length = 0;
        this._onNextCallbacks.length = 0;
        this._onInputFocus.length = 0;
        this._onRenderValuesChanged.length = 0;
    };
    return Numbers;
}());


// CONCATENATED MODULE: ./src/components/hand.ts


var hand_90 = Math.PI / 2;
/**The hand of the clock which rotates to show the minute/hour */
var hand_Hand = /** @class */ (function () {
    function Hand(elements) {
        this.elements = elements;
        this.angle = hand_90;
        this.setPositon(this.angle, Position.far);
    }
    Hand.prototype.setPositon = function (angle, position) {
        var _this = this;
        var delta = getAngleDelta(this.angle, angle);
        this.angle = this.angle + delta;
        this.elements.hands.forEach(function (h) { return h.style.transform = "rotate(" + _this.angle + "rad)"; });
        position === Position.near ?
            this.elements.ballPostion.forEach(function (b) { return b.classList.add("atp-b-pos-pm"); }) :
            this.elements.ballPostion.forEach(function (b) { return b.classList.remove("atp-b-pos-pm"); });
    };
    return Hand;
}());


// CONCATENATED MODULE: ./src/utils/distance.ts
var AmPm;
(function (AmPm) {
    AmPm["am"] = "am";
    AmPm["pm"] = "pm";
})(AmPm || (AmPm = {}));
function emToPx(em, fontSize) {
    return (fontSize ||
        parseFloat(window.getComputedStyle(document.body).fontSize ||
            "12")) * em;
}
/** With a 24 hour clock box (width/height) and a mouse position (left/top),
 * determine whether the use is pointing at an AM hour or a PM hour */
function getAMPM(left, top, width, height, fontSize) {
    var w = width / 2;
    var x = w - left;
    var y = (height / 2) - top;
    var distance = Math.sqrt((x * x) + (y * y));
    var maxPm = w - emToPx(2.45, fontSize);
    return distance > maxPm ? AmPm.am : AmPm.pm;
}
;


// CONCATENATED MODULE: ./src/utils/time.ts

var _30 = Math.PI / 6;
var _12 = Math.PI / 30;
var time_360 = Math.PI * 2;
var time_90 = Math.PI / 2;
/** Snap an angle to a given step. E.g. if angle = 22° and step = 10°, round down to 20° */
function snap(angle, step) {
    var a = angle;
    while (a < 0)
        a += time_360;
    var diff = a % step;
    if (diff <= step / 2) {
        return angle - diff;
    }
    return angle - diff + step;
}
/** Calculate the hour from the hand angle */
function getHours(handAngle, amPm) {
    handAngle = snap(handAngle, _30);
    var hour = parseInt((((handAngle - time_90) % time_360) / _30).toFixed());
    if (hour < 0)
        hour += 12;
    if (hour >= 12)
        hour -= 12;
    if (!hour) {
        if (amPm === AmPm.am)
            hour = 12;
    }
    else {
        if (amPm !== AmPm.am)
            hour += 12;
    }
    return {
        hour: hour,
        handAngle: handAngle
    };
}
var validate = /^\s*\d{1,2}\s*:\s*\d{1,2}\s*((am)|(pm))?\s*$/i;
function parseTime(time) {
    if (!time || !validate.test(time))
        return null;
    var split = time.split(":");
    var output = {
        hour: parseInt(split[0]),
        minute: parseInt(split[1])
    };
    if (output.minute < 0 || output.minute > 59)
        return null;
    if (/am/i.test(split[1])) {
        if (output.hour < 1 || output.hour > 12)
            return null;
    }
    else if (/pm/i.test(split[1])) {
        if (output.hour < 1 || output.hour > 12)
            return null;
        if (output.hour === 12)
            output.hour = 0;
        else
            output.hour += 12;
    }
    else {
        if (output.hour < 0 || output.hour > 23)
            return null;
    }
    return output;
}
/** Convert a 24 hour time into a string of the specified format */
function timeToString(h, m, mode) {
    if (mode === 24) {
        return ("0" + h).slice(-2) + ":" + ("0" + m).slice(-2);
    }
    else {
        var ampm = !h || h > 12 ? " PM" : " AM";
        if (!h)
            h = 12;
        else if (h > 12)
            h -= 12;
        return h + ":" + ("0" + m).slice(-2) + ampm;
    }
}
/** Calculate the minute from the hand angle */
function getMinutes(handAngle) {
    handAngle = snap(handAngle, _12);
    var minute = parseInt((((handAngle - time_90) % time_360) / _12).toFixed());
    while (minute < 0)
        minute += 60;
    while (minute >= 60)
        minute -= 60;
    return {
        minute: minute,
        handAngle: handAngle
    };
}
function convert24hTo12h(value) {
    if (!value)
        return 12;
    else if (value > 12)
        return value - 12;
    else
        return value;
}
function convert12hTo24h(value, amPm) {
    if (amPm === AmPm.am)
        return value;
    else if (amPm === AmPm.pm) {
        if (value === 12)
            return 0;
        return value + 12;
    }
    else {
        throw new Error("Expected \"am\" or \"pm\": \"" + amPm + "\"");
    }
}
/** The default time format (12h/24h) based on the value of Date.prototype.toLocaleTimeString */
var defaultMode = (function () {
    var locale = new Date("January 01, 2000 13:00:00 GMT+00:00").toLocaleTimeString();
    return /(AM)|(PM)/i.test(locale) ? 12 : 24;
}());


// CONCATENATED MODULE: ./src/components/hours.ts
var __extends = (undefined && undefined.__extends) || (function () {
    var extendStatics = Object.setPrototypeOf ||
        ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
        function (d, b) { for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p]; };
    return function (d, b) {
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();





var hours_90 = Math.PI / 2;
var hours_30 = Math.PI / 6;
/**A component to manage the hours */
var hours_Hours = /** @class */ (function (_super) {
    __extends(Hours, _super);
    function Hours(hourInput, elements, value) {
        var _this = _super.call(this, hourInput, elements, value) || this;
        _this.hourInput = hourInput;
        _this.mode = 24;
        _this.am = elements.am;
        _this._toAm = registerMouseEvent(_this.am, "click", function () { return _this.setTo12Hr(AmPm.am); });
        _this.pm = elements.pm;
        _this._toPm = registerMouseEvent(_this.pm, "click", function () { return _this.setTo12Hr(AmPm.pm); });
        _this.amPmButtons = elements.amPmButtons;
        _this.showHideAmPm();
        _this.onValueChanged(function () { return _this.highlightAmPm(); });
        _this.highlightAmPm();
        return _this;
    }
    /** Returns a label. The label is for accessability/screen reading purposes */
    Hours.prototype.getLabel = function () { return "Hours " + this.mode + "h format"; };
    /** Show/hide the AM/PM buttons based on the current "mode" */
    Hours.prototype.showHideAmPm = function () {
        if (this.mode === 12) {
            this.amPmButtons.style.display = "";
            this.amPmButtons.removeAttribute("aria-hidden");
        }
        else {
            this.amPmButtons.style.display = "none";
            this.amPmButtons.setAttribute("aria-hidden", "true");
        }
    };
    /** Highlight the correct AM/PM button based on the current hour */
    Hours.prototype.highlightAmPm = function () {
        if (!this.value.value || this.value.value > 12) {
            this.am.removeAttribute("aria-pressed");
            this.pm.setAttribute("aria-pressed", "");
        }
        else {
            this.pm.removeAttribute("aria-pressed");
            this.am.setAttribute("aria-pressed", "");
        }
    };
    /** Set the mode to 12h. Optionally , specify whether the time is AM or PM */
    Hours.prototype.setTo12Hr = function (amPm) {
        var value = this.value.value;
        if (amPm) {
            value = convert12hTo24h(convert24hTo12h(value), amPm);
        }
        this.mode = 12;
        this.showHideAmPm();
        this.hidePMHours();
        var ig = this.ignoreNumberInputChangeEvent();
        try {
            this.hourInput.setTo12Hr(amPm);
        }
        finally {
            ig();
        }
        // accessability label changes based on mode
        this.setLabel();
        this.set(value);
    };
    /** Set the mode to 24h. */
    Hours.prototype.setTo24Hr = function () {
        this.mode = 24;
        this.showHideAmPm();
        this.showPMHours();
        var ig = this.ignoreNumberInputChangeEvent();
        try {
            this.hourInput.setTo24Hr();
        }
        finally {
            ig();
        }
        // accessability label changes based on mode
        this.setLabel();
        this.set(this.value.value);
    };
    /** Hide hours 00 and 13 - 23 for 12h format */
    Hours.prototype.hidePMHours = function () {
        this.elements.numbers
            .slice(0, 1)
            .concat(this.elements.numbers.slice(13))
            .forEach(function (x) { return x.style.display = "none"; });
    };
    /** Show hours 00 and 13 - 23 for 24h format */
    Hours.prototype.showPMHours = function () {
        this.elements.numbers
            .slice(0, 1)
            .concat(this.elements.numbers.slice(13))
            .forEach(function (x) { return x.style.display = ""; });
    };
    /** Get the html element of the number currently selected */
    Hours.prototype.getSelectedNumberElement = function () {
        if (this.mode === 12) {
            return this.elements.numbers[convert24hTo12h(this.value.value)];
        }
        return _super.prototype.getSelectedNumberElement.call(this);
    };
    /** Get the hour, angle, etc... based on the mouse position */
    Hours.prototype.getValuesFromPosition = function (x, y) {
        var angle = getAngle(x, y, this.elements.containerElement.offsetWidth, this.elements.containerElement.offsetHeight);
        var amPm = this.mode === 24 ?
            getAMPM(x, y, this.elements.containerElement.offsetWidth, this.elements.containerElement.offsetHeight, this.fontSize) :
            this.value.value && this.value.value <= 12 ? AmPm.am : AmPm.pm;
        var value = getHours(angle, amPm);
        return {
            angle: value.handAngle,
            value: value.hour,
            position: this.mode === 12 || amPm === AmPm.am ? Position.far : Position.near
        };
    };
    /** Get the hour, angle, etc... based on the hour */
    Hours.prototype.getValuesFromValue = function (value) {
        value = parseInt(value.toFixed()) % 24;
        var angle = (value * hours_30) + hours_90;
        return {
            angle: angle,
            value: value,
            position: this.mode === 12 || (value && value <= 12) ? Position.far : Position.near
        };
    };
    Hours.prototype.dispose = function () {
        _super.prototype.dispose.call(this);
        this._toAm();
        this._toPm();
    };
    return Hours;
}(numbers_Numbers));


// CONCATENATED MODULE: ./src/assets/template.ts
// THIS IS AN AUTOGENERATED FILE, BUILD USING ./tools/buildHtmlTemplate.js
function create(model) {
    var el = document.createElement('div');
    el.innerHTML = "<div class=\"atp atp-background-color\" role=\"form\" aria-describedby=\"" + model.title + "\"><label style=\"display: none\" id=\"" + model.title + "\">Enter time</label><div class=\"atp-time atp-color--primary mdl-color--primary\"><label style=\"display: none\" for=\"" + model.hour + "\" class=\"atp-hour-label\">Hours</label><input type=\"text\" class=\"atp-hour\" id=\"" + model.hour + "\" />:<label style=\"display: none\" for=\"" + model.minute + "\" class=\"atp-minute-label\">Minutes</label><input type=\"text\" class=\"atp-minute\" id=\"" + model.minute + "\" /><div class=\"atp-ampm\"><label style=\"display: none\" for=\"" + model.am + "\">Change to AM</label><button class=\"atp-am\" id=\"" + model.am + "\">am</button><label style=\"display: none\" for=\"" + model.pm + "\">Change to PM</label><button class=\"atp-pm\" id=\"" + model.pm + "\">pm</button></div></div><div class=\"atp-clock-cnt\"><div class=\"atp-clock\" aria-hidden=\"true\"><div class=\"atp-face atp-face-color\"></div><div class=\"atp-h-cnt-cnt\"><div class=\"atp-h-cnt\"><div class=\"atp-b-pos\"></div><div class=\"atp-b atp-color--primary mdl-color--primary\"></div></div></div><div class=\"atp-ns atp-hours atp-number-color\"><div class=\"atp-n-box\"><div class=\"atp-n-cnt atp-n-cnt-0\"><div class=\"atp-n atp-n-0\">12</div><div class=\"atp-n-pad\"></div><div class=\"atp-n atp-n-0\">00</div></div></div><div class=\"atp-n-box\"><div class=\"atp-n-cnt atp-n-cnt-1\"><div class=\"atp-n atp-n-1\">01</div><div class=\"atp-n-pad\"></div><div class=\"atp-n atp-n-1\">13</div></div></div><div class=\"atp-n-box\"><div class=\"atp-n-cnt atp-n-cnt-2\"><div class=\"atp-n atp-n-2\">02</div><div class=\"atp-n-pad\"></div><div class=\"atp-n atp-n-2\">14</div></div></div><div class=\"atp-n-box\"><div class=\"atp-n-cnt atp-n-cnt-3\"><div class=\"atp-n atp-n-3\">03</div><div class=\"atp-n-pad\"></div><div class=\"atp-n atp-n-3\">15</div></div></div><div class=\"atp-n-box\"><div class=\"atp-n-cnt atp-n-cnt-4\"><div class=\"atp-n atp-n-4\">04</div><div class=\"atp-n-pad\"></div><div class=\"atp-n atp-n-4\">16</div></div></div><div class=\"atp-n-box\"><div class=\"atp-n-cnt atp-n-cnt-5\"><div class=\"atp-n atp-n-5\">05</div><div class=\"atp-n-pad\"></div><div class=\"atp-n atp-n-5\">17</div></div></div><div class=\"atp-n-box\"><div class=\"atp-n-cnt atp-n-cnt-6\"><div class=\"atp-n atp-n-6\">06</div><div class=\"atp-n-pad\"></div><div class=\"atp-n atp-n-6\">18</div></div></div><div class=\"atp-n-box\"><div class=\"atp-n-cnt atp-n-cnt-7\"><div class=\"atp-n atp-n-7\">07</div><div class=\"atp-n-pad\"></div><div class=\"atp-n atp-n-7\">19</div></div></div><div class=\"atp-n-box\"><div class=\"atp-n-cnt atp-n-cnt-8\"><div class=\"atp-n atp-n-8\">08</div><div class=\"atp-n-pad\"></div><div class=\"atp-n atp-n-8\">20</div></div></div><div class=\"atp-n-box\"><div class=\"atp-n-cnt atp-n-cnt-9\"><div class=\"atp-n atp-n-9\">09</div><div class=\"atp-n-pad\"></div><div class=\"atp-n atp-n-9\">21</div></div></div><div class=\"atp-n-box\"><div class=\"atp-n-cnt atp-n-cnt-10\"><div class=\"atp-n atp-n-10\">10</div><div class=\"atp-n-pad\"></div><div class=\"atp-n atp-n-10\">22</div></div></div><div class=\"atp-n-box\"><div class=\"atp-n-cnt atp-n-cnt-11\"><div class=\"atp-n atp-n-11\">11</div><div class=\"atp-n-pad\"></div><div class=\"atp-n atp-n-11\">23</div></div></div></div><div class=\"atp-ns atp-minutes atp-number-color\"><div class=\"atp-n-cnt atp-n-cnt-0\"><div class=\"atp-n atp-n-0\">00</div></div><div class=\"atp-n-box\"><div class=\"atp-n-cnt atp-n-cnt-1\"><div class=\"atp-n atp-n-1\">05</div></div></div><div class=\"atp-n-box\"><div class=\"atp-n-cnt atp-n-cnt-2\"><div class=\"atp-n atp-n-2\">10</div></div></div><div class=\"atp-n-box\"><div class=\"atp-n-cnt atp-n-cnt-3\"><div class=\"atp-n atp-n-3\">15</div></div></div><div class=\"atp-n-box\"><div class=\"atp-n-cnt atp-n-cnt-4\"><div class=\"atp-n atp-n-4\">20</div></div></div><div class=\"atp-n-box\"><div class=\"atp-n-cnt atp-n-cnt-5\"><div class=\"atp-n atp-n-5\">25</div></div></div><div class=\"atp-n-box\"><div class=\"atp-n-cnt atp-n-cnt-6\"><div class=\"atp-n atp-n-6\">30</div></div></div><div class=\"atp-n-box\"><div class=\"atp-n-cnt atp-n-cnt-7\"><div class=\"atp-n atp-n-7\">35</div></div></div><div class=\"atp-n-box\"><div class=\"atp-n-cnt atp-n-cnt-8\"><div class=\"atp-n atp-n-8\">40</div></div></div><div class=\"atp-n-box\"><div class=\"atp-n-cnt atp-n-cnt-9\"><div class=\"atp-n atp-n-9\">45</div></div></div><div class=\"atp-n-box\"><div class=\"atp-n-cnt atp-n-cnt-10\"><div class=\"atp-n atp-n-10\">50</div></div></div><div class=\"atp-n-box\"><div class=\"atp-n-cnt atp-n-cnt-11\"><div class=\"atp-n atp-n-11\">55</div></div></div></div><div class=\"atp-h-cnt-cnt\"><div class=\"atp-h-cnt\"><div class=\"atp-b-pos\"></div><div class=\"atp-b-spacer\"></div><div class=\"atp-h atp-color--primary mdl-color--primary\"></div></div></div><div class=\"atp-h-cnt-cnt atp-h-cnt-cnt-dot\"><div class=\"atp-h-dot atp-color--primary mdl-color--primary\"></div></div></div><div class=\"atp-clock-btn\"><button class=\"atp-ok atp-button mdl-button atp-button atp-button--primary mdl-button--primary atp-enforce-font-size\">ok</button><button class=\"atp-cancel atp-button mdl-button atp-button atp-button--primary mdl-button--primary atp-enforce-font-size\">cancel</button></div></div></div>";
    var child = el.firstChild;
    el.removeChild(child);
    return child;
}


// CONCATENATED MODULE: ./src/components/htmlTree.ts


var getId = (function () {
    var i = Math.floor(Math.random() * 100000);
    return function () { return "atp-" + ++i; };
}());
function buildHtmlModel() {
    var id = getId();
    return {
        hour: id + "-hour",
        minute: id + "-minute",
        am: id + "-am",
        pm: id + "-pm",
        title: id + "-title"
    };
}
function getPxValue(width) {
    // if value has no units, interpret as px
    if (/^\s*\d+(\.\d*)?\s*$/.test(width))
        width += "px";
    if (/px\s*$/.test(width))
        return parseFloat(width);
    var test = document.createElement("div");
    test.style.width = width;
    document.body.appendChild(test);
    var w = test.offsetWidth;
    removeChildSafe(document.body, test);
    return w;
}
// const fontMultiplier = 6 / 75;
var fontMultiplier = 4 / 75;
function getFontSize(width) {
    // don't set font size for em or %
    if (/(em|%)\s*$/.test(width))
        return null;
    var widthPx = getPxValue(width);
    if (isNaN(widthPx))
        throw new Error("Invalid width value: " + width);
    if (widthPx <= 0)
        console.warn("Width value \"" + width + "\" came to " + widthPx + "px");
    return widthPx * fontMultiplier;
}
/** Creates or uses existing element and populates it with the html template */
var htmlTree_HtmlTree = /** @class */ (function () {
    function HtmlTree(width, rootHtmlElement) {
        this.element = create(buildHtmlModel());
        if (rootHtmlElement) {
            rootHtmlElement.innerHTML = "";
            rootHtmlElement.appendChild(this.element);
        }
        this.setWidth(width);
    }
    HtmlTree.prototype.setWidth = function (widthValue) {
        this.element.style.width = widthValue;
        var fs = getFontSize(widthValue);
        this.element.style.fontSize = fs != null ? fs + "px" : null;
    };
    HtmlTree.prototype.dispose = function () {
        if (this.element.parentElement) {
            this.element.parentElement.removeChild(this.element);
        }
    };
    return HtmlTree;
}());


// CONCATENATED MODULE: ./src/components/minutes.ts
var minutes_extends = (undefined && undefined.__extends) || (function () {
    var extendStatics = Object.setPrototypeOf ||
        ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
        function (d, b) { for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p]; };
    return function (d, b) {
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();



var minutes_90 = Math.PI / 2;
var _6 = Math.PI / 30;
var minutes_Minutes = /** @class */ (function (_super) {
    minutes_extends(Minutes, _super);
    function Minutes() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    /** Get the minute, angle, etc... based on the mouse position */
    Minutes.prototype.getValuesFromPosition = function (x, y) {
        var angle = getAngle(x, y, this.elements.containerElement.offsetWidth, this.elements.containerElement.offsetHeight);
        var value = getMinutes(angle);
        return {
            angle: value.handAngle,
            value: value.minute,
            position: Position.far
        };
    };
    /** Returns a label. The label is for accessability/screen reading purposes */
    Minutes.prototype.getLabel = function () { return "Minutes"; };
    /** Get the minute, angle, etc... based on the minute */
    Minutes.prototype.getValuesFromValue = function (value) {
        value = parseInt(value.toFixed()) % 60;
        var angle = (value * _6) + minutes_90;
        return {
            angle: angle,
            value: value,
            position: Position.far
        };
    };
    return Minutes;
}(numbers_Numbers));


// CONCATENATED MODULE: ./src/utils/numberKeyPressInterpreters.ts
var numberKeyPressInterpreters_assign = (undefined && undefined.__assign) || Object.assign || function(t) {
    for (var s, i = 1, n = arguments.length; i < n; i++) {
        s = arguments[i];
        for (var p in s) if (Object.prototype.hasOwnProperty.call(s, p))
            t[p] = s[p];
    }
    return t;
};
/** Increase a numer with loop back over the max value */
function increase(val, max) {
    var v = parseInt(val) + 1;
    return v > max ? 0 : v;
}
/** Decrease a numer with loop back over the min value */
function decrease(val, max) {
    var v = parseInt(val) - 1;
    return v < 0 ? max : v;
}
/** Get the value and mouse position after a number key is pressed */
function getNewElementValues(element, key, max) {
    var actualStart = element.selectionStart || 0;
    var start = actualStart > 1 ?
        1 :
        actualStart;
    var val1 = (element.value || "").substr(0, start);
    var val2 = (element.value || "").substr(start + 1);
    var value = parseInt("" + val1 + key + val2);
    if (isNaN(value) || value < 0)
        return null;
    if (value <= max) {
        var skip = 0;
        if (!val1 && !val2 && value * 10 > max) {
            // special case for when only 1 digit fits in the text box
            skip++;
        }
        return {
            value: value,
            nextPosition: actualStart + 1 + skip
        };
    }
    if (!actualStart) {
        // set last digit to 0 and try again
        value -= value % 10;
        if (value <= max)
            return {
                value: value,
                nextPosition: actualStart + 1
            };
        // just use the key as is
        value = parseInt(key);
        if (!isNaN(value) && value <= max)
            return {
                value: value,
                // skipped an extra digit by using first key
                nextPosition: actualStart + 2
            };
    }
    return null;
}
var numberKey = /^\d$/;
var fKey = /^F\d+$/;
/** Get values which can inform a decision on what to do when a key is pressed */
function keyPressDetails(element, e, max) {
    var handled = true;
    switch (e.key) {
        case "ArrowUp":
        case "Up":
            return {
                handled: true,
                value: increase(element.value, max)
            };
        case "ArrowDown":
        case "Down":
            return {
                handled: true,
                value: decrease(element.value, max)
            };
        case "ArrowRight":
        case "Right":
            var nextPosition = (element.selectionStart || 0) + 1;
            return {
                handled: nextPosition > 2,
                nextPosition: nextPosition > 2 ? nextPosition : undefined
            };
        case "ArrowLeft":
        case "Left":
            var nextPosition = (element.selectionStart || 0) - 1;
            return {
                handled: nextPosition < 0,
                nextPosition: nextPosition < 0 ? nextPosition : undefined
            };
        case "Tab":
            return {
                handled: false
            };
        default:
            if (numberKey.test(e.key)) {
                return numberKeyPressInterpreters_assign({ handled: true }, getNewElementValues(element, e.key, max));
            }
            else if (fKey.test(e.key)) {
                return {
                    handled: false
                };
            }
    }
    return { handled: true };
}


// CONCATENATED MODULE: ./src/components/numberInput.ts


/** Component to manage the number number textbox (e.g. the hour/minute) */
var numberInput_NumberInput = /** @class */ (function () {
    function NumberInput(input) {
        var _this = this;
        this.input = input;
        this.value = 0;
        this._onFocus = [];
        this._onNextCallbacks = [];
        this._onPreviousCallbacks = [];
        this._timeChangedCallbacks = [];
        this._keyPressHandler = registerKeyEvent(input, "keydown", function (e) { return _this.keyDown(e); });
        this._focusHandler = registerKeyEvent(input, "focus", function (e) { return _this.focusOnInput(); });
    }
    /**Callback for when element receives focus */
    NumberInput.prototype.onFocus = function (f) {
        this._onFocus.push(f);
    };
    /**Callback for when element is complete (like tab) */
    NumberInput.prototype.onNext = function (f) {
        this._onNextCallbacks.push(f);
    };
    /**Callback for when element is complete (like shift tab) */
    NumberInput.prototype.onPrevious = function (f) {
        this._onPreviousCallbacks.push(f);
    };
    /**Callback for when value in the textbox has changed  */
    NumberInput.prototype.onTimeChanged = function (callback) {
        this._timeChangedCallbacks.push(callback);
    };
    NumberInput.prototype.keyDown = function (e) {
        var details = keyPressDetails(this.input, e, this.getMaxValue());
        if (details.handled)
            e.preventDefault();
        if (details.value != null) {
            this._set(details.value);
        }
        if (details.nextPosition != null) {
            if (details.nextPosition < 0) {
                this._onPreviousCallbacks.forEach(function (f) { return f(); });
            }
            else {
                this.input.selectionEnd = details.nextPosition;
                this.input.selectionStart = details.nextPosition;
                if (details.nextPosition > 1) {
                    this._onNextCallbacks.forEach(function (f) { return f(); });
                }
            }
        }
    };
    NumberInput.prototype.focusOnInput = function () {
        this._onFocus
            .slice(0)
            .forEach(function (f) { return f(); });
    };
    /** Set a value in the textbox */
    NumberInput.prototype.set = function (value) {
        if (value < 0 || value > this.getMaxValue())
            throw new Error("Invalid value \"" + value + "\"");
        this._set(parseInt(value.toFixed()));
    };
    NumberInput.prototype._set = function (value) {
        var changed = this.value !== value;
        this.value = value;
        this.input.value = this.transformInputValue(value);
        if (changed) {
            this._timeChangedCallbacks
                .slice(0)
                .forEach(function (f) { return f(value); });
        }
    };
    /**
     * @param {boolean} [focusInput=true] If true, will focus the cursor on the input also
     */
    NumberInput.prototype.focus = function (focusInput) {
        if (focusInput === void 0) { focusInput = true; }
        this.input.classList.add("atp-focus");
        if (focusInput) {
            this.input.focus();
            this.input.selectionStart = 0;
            this.input.selectionEnd = 0;
        }
    };
    NumberInput.prototype.blur = function () {
        this.input.classList.remove("atp-focus");
    };
    NumberInput.prototype.dispose = function () {
        this._focusHandler();
        this._keyPressHandler();
        this._onFocus.length = 0;
        this._onPreviousCallbacks.length = 0;
        this._onNextCallbacks.length = 0;
        this._timeChangedCallbacks.length = 0;
    };
    return NumberInput;
}());


// CONCATENATED MODULE: ./src/components/hourInput.ts
var hourInput_extends = (undefined && undefined.__extends) || (function () {
    var extendStatics = Object.setPrototypeOf ||
        ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
        function (d, b) { for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p]; };
    return function (d, b) {
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();


/** An input to manage hours */
var hourInput_HourInput = /** @class */ (function (_super) {
    hourInput_extends(HourInput, _super);
    function HourInput() {
        var _this = _super !== null && _super.apply(this, arguments) || this;
        _this.mode = 24;
        return _this;
    }
    HourInput.prototype.getMaxValue = function () { return 23; };
    /**Set to 12h mode and set am/pm if necessary */
    HourInput.prototype.setTo12Hr = function (amPm) {
        var value = this.value;
        if (amPm) {
            value = convert12hTo24h(convert24hTo12h(value), amPm);
        }
        this.mode = 12;
        this.set(value);
    };
    HourInput.prototype.setTo24Hr = function () {
        this.mode = 24;
        this.set(this.value);
    };
    /**Convert a 24 hour value into a 12 hour value if necessary */
    HourInput.prototype.transformInputValue = function (value) {
        if (this.mode === 12) {
            if (!value)
                value = 12;
            else if (value > 12)
                value -= 12;
            return value.toString();
        }
        return ("0" + value).slice(-2);
    };
    return HourInput;
}(numberInput_NumberInput));


// CONCATENATED MODULE: ./src/components/minuteInput.ts
var minuteInput_extends = (undefined && undefined.__extends) || (function () {
    var extendStatics = Object.setPrototypeOf ||
        ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
        function (d, b) { for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p]; };
    return function (d, b) {
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();

/** A numner input for mintes */
var MinuteInput = /** @class */ (function (_super) {
    minuteInput_extends(MinuteInput, _super);
    function MinuteInput() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    MinuteInput.prototype.getMaxValue = function () { return 59; };
    MinuteInput.prototype.transformInputValue = function (value) {
        return ("0" + value).slice(-2);
    };
    return MinuteInput;
}(numberInput_NumberInput));


// CONCATENATED MODULE: ./src/di.ts







function toArray(xs) {
    return Array.prototype.slice.call(xs);
}
/** A DI container which creates components and manages their lifecycles */
var di_DiContext = /** @class */ (function () {
    function DiContext(config, rootHtmlElement) {
        this.config = config;
        this.disposables = [];
        this.htmlTree = new htmlTree_HtmlTree(config.width, rootHtmlElement);
        this.disposables.push(this.htmlTree);
    }
    DiContext.prototype.getRootElement = function () {
        return this.htmlTree.element;
    };
    DiContext.prototype.getInnerElement = function (selector) {
        var el = this.getRootElement().querySelectorAll(selector);
        if (el.length !== 1) {
            var message = el.length ? "Too many elements" : "Cannot find element";
            throw new Error(message + " \"" + selector + "\".");
        }
        return el[0];
    };
    DiContext.prototype.buildHoursElementList = function (index) {
        var list = [];
        for (var i = 0; i < 12; i++) {
            list[i] = this.getRootElement().querySelectorAll(".atp-hours .atp-n-" + i)[index];
        }
        return list.map(function (el, i) {
            if (!el)
                throw new Error("Invalid hours element " + i + ".");
            return el;
        });
    };
    DiContext.prototype.buildHoursElements = function () {
        var hours = this
            .buildHoursElementList(0)
            .concat(this.buildHoursElementList(1));
        // re-arrange numbers to put the 12 and 00 at the correct indexes
        hours.splice(11, 0, hours.splice(0, 1)[0]);
        hours.splice(0, 0, hours.splice(12, 1)[0]);
        return {
            numbers: hours,
            containerElement: this.getInnerElement(".atp-hours"),
            amPmButtons: this.getInnerElement(".atp-ampm"),
            am: this.getInnerElement(".atp-am"),
            pm: this.getInnerElement(".atp-pm"),
            label: this.getInnerElement(".atp-hour-label")
        };
    };
    DiContext.prototype.buildHoursInput = function () {
        if (!this.hourInput) {
            var el = this.getInnerElement(".atp-hour");
            this.hourInput = new hourInput_HourInput(el);
            this.disposables.push(this.hourInput);
        }
        return this.hourInput;
    };
    DiContext.prototype.buildHours = function () {
        if (!this.hours) {
            this.hours = new hours_Hours(this.buildHoursInput(), this.buildHoursElements(), this.config.time.hour);
            this.disposables.push(this.hours);
        }
        return this.hours;
    };
    DiContext.prototype.buildMinutesElementList = function () {
        var list = [];
        for (var i = 0; i < 12; i++) {
            list[(i * 5) % 60] = this.getRootElement().querySelectorAll(".atp-minutes .atp-n-" + i)[0];
        }
        return list.map(function (el, i) {
            if (!el)
                throw new Error("Invalid hours element " + i + ".");
            return el;
        });
    };
    DiContext.prototype.buildMinutesElements = function () {
        return {
            containerElement: this.getInnerElement(".atp-minutes"),
            numbers: this.buildMinutesElementList(),
            label: this.getInnerElement(".atp-minute-label")
        };
    };
    DiContext.prototype.buildMinutesInput = function () {
        if (!this.minuteInput) {
            var el = this.getInnerElement(".atp-minute");
            this.minuteInput = new MinuteInput(el);
            this.disposables.push(this.minuteInput);
        }
        return this.minuteInput;
    };
    DiContext.prototype.buildMinutes = function () {
        if (!this.minutes) {
            this.minutes = new minutes_Minutes(this.buildMinutesInput(), this.buildMinutesElements(), this.config.time.minute);
            this.disposables.push(this.minutes);
        }
        return this.minutes;
    };
    DiContext.prototype.buildHandElements = function () {
        return {
            ballPostion: toArray(this.getRootElement().querySelectorAll(".atp-b-pos")),
            hands: toArray(this.getRootElement().querySelectorAll(".atp-h-cnt"))
        };
    };
    DiContext.prototype.buildHand = function () {
        return this.hand || (this.hand = new hand_Hand(this.buildHandElements()));
    };
    DiContext.prototype.buildTimePickerElements = function () {
        return {
            okButton: this.getInnerElement(".atp-ok"),
            cancelButton: this.getInnerElement(".atp-cancel"),
            clock: this.getInnerElement(".atp-clock")
        };
    };
    DiContext.prototype.buildTimePicker = function () {
        if (!this.timePicker) {
            this.timePicker = new timePicker_TimePicker(this.buildTimePickerElements(), this.buildHours(), this.buildMinutes(), this.buildHand(), this.config.mode, this.config.focusOnInput);
            this.disposables.push(this.timePicker);
        }
        return this.timePicker;
    };
    DiContext.prototype.dispose = function () {
        this.disposables
            .splice(0, Number.MAX_VALUE)
            .forEach(function (x) { return x.dispose(); });
    };
    return DiContext;
}());


// CONCATENATED MODULE: ./src/init/parseInputs.ts
function parseTimeValues(hour, minute) {
    var h = 0;
    if (hour != null) {
        h = parseInt(hour);
        if (isNaN(h) || h < 0 || h > 23) {
            throw new Error("The hr (" + hour + ") argument must be between 0 and 23.");
        }
    }
    var m = 0;
    if (minute != null) {
        m = parseInt(minute);
        if (isNaN(m) || m < 0 || m > 59) {
            throw new Error("The mn (" + minute + ") argument must be between 0 and 59.");
        }
    }
    return {
        hour: h,
        minute: m
    };
}
function parseTimeInput(time) {
    if (!time)
        return { hour: 0, minute: 0 };
    if (time instanceof Date) {
        return {
            hour: time.getHours(),
            minute: time.getMinutes()
        };
    }
    else {
        return parseTimeValues(time.hour, time.minute);
    }
}
function parseHtmlElement(el) {
    if (el == null)
        return undefined;
    if (el instanceof HTMLElement)
        return el;
    throw new Error("The element must be a HTMLElement");
}
function parseMode(mode) {
    if (mode == null)
        return 24;
    var m = parseInt(mode);
    if (m === 12)
        return 12;
    else if (m === 24)
        return 24;
    else
        throw new Error("The mode argument must be null, undefined, 12 or 24.");
}
function parseWidth(width) {
    if (width == null)
        return "300px";
    if (typeof width === "number") {
        if (width < 0)
            throw new Error("The width (" + width + ") argument must be >= 0.");
        return width + "px";
    }
    else if (typeof width === "string") {
        return width;
    }
    else {
        throw new Error("The width (" + width + ") argument must be a number or string.");
    }
}


// CONCATENATED MODULE: ./src/init/publicTimePicker.ts
/**Wrap a DI context in a new public TimePicker object.
 * The pulic TimePicker is more fault tolerant and is made
 * to interact with js rather than ts
 * It also has dispose logic and an onDispose event */
function publicTimePicker(context) {
    var timePicker = context.buildTimePicker();
    var element = context.getRootElement();
    var onDispose = [];
    function dispose() {
        context.dispose();
        onDispose
            .splice(0, Number.MAX_VALUE)
            .forEach(function (f) { return f(); });
    }
    timePicker.onOk(dispose);
    timePicker.onCancel(dispose);
    return {
        element: element,
        setWidth: function (width) {
            context.htmlTree.setWidth(width == null || width === "" ?
                "100%" :
                typeof width === "number" ? width + "px" : width.toString());
        },
        getTime: function () { return timePicker.getTime(); },
        setTime: function (hours, minutes) {
            var h = parseInt(hours);
            if (isNaN(h))
                throw new Error("The hours value \"" + hours + "\" must be a number");
            var m = parseInt(minutes);
            if (isNaN(m))
                throw new Error("The minutes value \"" + minutes + "\" must be a number");
            if (h < 0 || h > 23)
                throw new Error("The hours value \"" + h + "\" must be between 0 and 23");
            if (m < 0 || m > 59)
                throw new Error("The minutes value \"" + m + "\" must be between 0 and 59");
            timePicker.setTime(h, m);
        },
        set12h: function () { return timePicker.setMode(12); },
        set24h: function () { return timePicker.setMode(24); },
        showHours: function () { return timePicker.showHours(true); },
        showMinutes: function () { return timePicker.showMinutes(); },
        ok: function () { return timePicker.okClick(); },
        cancel: function () { return timePicker.cancelClick(); },
        onTimeChanged: function (callback) {
            if (typeof callback !== "function") {
                throw new Error("onOk callback must be a function");
            }
            timePicker.onTimeChanged(callback);
        },
        onOk: function (callback) {
            if (typeof callback !== "function") {
                throw new Error("onOk callback must be a function");
            }
            timePicker.onOk(callback);
        },
        onCancel: function (callback) {
            if (typeof callback !== "function") {
                throw new Error("onCancel callback must be a function");
            }
            timePicker.onCancel(callback);
        },
        onDispose: function (callback) {
            if (typeof callback !== "function") {
                throw new Error("onCancel callback must be a function");
            }
            onDispose.push(callback);
        },
        dispose: dispose
    };
}


// CONCATENATED MODULE: ./src/init/timePicker.ts



function parseTimePickerData(input) {
    if (!input)
        input = {};
    return {
        config: {
            time: parseTimeInput(input.time),
            mode: parseMode(input.mode),
            width: parseWidth(input.width),
            focusOnInput: !!input.focus
        },
        element: parseHtmlElement(input.element)
    };
}
/** Create a new time picker. The timepicker lives in the "element" return value which can then be appended to the DOM */
function timePicker_create(input) {
    var _input = parseTimePickerData(input);
    var context = new di_DiContext(_input.config, _input.element);
    return publicTimePicker(context);
}


// CONCATENATED MODULE: ./src/init/timePickerModal.ts




function parseInputs(input) {
    if (!input)
        input = {};
    return {
        config: {
            time: parseTimeInput(input.time),
            mode: parseMode(input.mode),
            width: parseWidth(input.width),
            focusOnInput: true
        }
    };
}
/** Create a new time picker and render in a modal */
function timePickerModal_create(input) {
    var _input = parseInputs(input);
    var context = new di_DiContext(_input.config);
    var timePicker = publicTimePicker(context);
    var modal = createModal(timePicker.element);
    modal.onClickOrEsc(function () { return timePicker.cancel(); });
    timePicker.onDispose(modal.dispose);
    // focus on the first textbox in the time picker
    context.getInnerElement(".atp-hour").focus();
    return timePicker;
}


// CONCATENATED MODULE: ./src/init/timePickerInput.ts




/** Create a new time picker and render in a modal each time an input is focused */
function timePickerInput_create(input) {
    if (!input || !(input.inputElement instanceof HTMLInputElement)) {
        throw new Error("The inputElement must be a html input element");
    }
    var modal = null;
    var el = input.inputElement;
    var displayModal = function () {
        modal = timePickerModal_create({
            mode: input.mode,
            width: input.width,
            time: parseTime(el.value)
        });
        modal.onOk(function (h, m) {
            // assuming that the timePickerModal call will have validated the mode
            el.value = timeToString(h, m, input.mode || 24);
        });
        modal.onDispose(function () { return modal = null; });
    };
    var dispose = [
        registerEvent(el, "focus", displayModal),
        // prevent use input on input
        registerEvent(el, "keyup", function (e) { return e.preventDefault(); }),
        registerEvent(el, "keydown", function (e) { return e.preventDefault(); }),
        registerEvent(el, "keypress", function (e) { return e.preventDefault(); })
    ];
    var mode = parseMode(input.mode);
    if (input.time) {
        var t = parseTimeInput(input.time);
        el.value = timeToString(t.hour, t.minute, mode);
    }
    if (document.activeElement === el)
        displayModal();
    return {
        getTime: function () {
            if (modal)
                return modal.getTime();
            return parseTime(el.value || "");
        },
        setTime: function (hour, minute, force) {
            if (force === void 0) { force = false; }
            if (modal) {
                modal.setTime(hour, minute);
            }
            if (!modal || force) {
                var time = parseTimeValues(hour, minute);
                el.value = timeToString(time.hour, time.minute, mode);
            }
        },
        dispose: function () {
            if (modal)
                modal.dispose();
            dispose
                .splice(0, Number.MAX_VALUE)
                .forEach(function (f) { return f(); });
        }
    };
}


// CONCATENATED MODULE: ./src/assets/style.ts
// THIS IS AN AUTOGENERATED FILE, BUILD USING ./tools/buildCss.js
var css = ".atp-number-color{color:black;}.atp-number-selected{color:white;}.atp-background-color{background-color:white;}.atp-face-color{background-color:rgb(238, 238, 238);}.atp{width:100%;cursor:default;box-shadow:rgba(0, 0, 0, 0.25) 0px 14px 45px, rgba(0, 0, 0, 0.22) 0px 10px 18px;font-family:\"Helvetica\", \"Arial\", sans-serif;}.atp-clock-cnt{padding:2em 1em 1em 1em;}.atp-clock{width:100%;position:relative;-webkit-user-select:none;-khtml-user-select:none;-moz-user-select:none;-o-user-select:none;user-select:none;}.atp-clock::before{content:\"\";display:block;padding-top:100%; 	}.atp-clock>*{width:100%;height:100%;position:absolute;top:0;left:0;}.atp-face{border-radius:100%;}.atp-ns{transform:scale(1);transition:transform 0.3s, opacity 0.05s;display:flex;}.atp-h-cnt-cnt{display:flex;align-items:center;}.atp-h-cnt-cnt-dot{justify-content:center;}.atp-h-cnt{height:1.65em;display:flex;transition:transform 0.1s;transform-origin:100% 50%;width:50%;align-items:center;transform:rotate(1.5708rad);}.atp-h-dot{height:0.3em;width:0.3em;border-radius:50%;}.atp-h{height:0.1em;flex:1;}.atp-n-box{width:100%;height:100%;top:0;left:0;position:absolute;display:flex;align-items:center;}.atp-n-cnt{width:100%;display:flex;align-items:center;padding-left:0.5em;}.atp-n-cnt>*{float:left;}.atp-n{width:1.3em;text-align:center;line-height:1.3em;height:1.3em;transition:color 0.1s;}.atp-clock *::selection{background:transparent;}.atp-n-pad{width:0.8em;height:1px;}.atp-n-cnt-1{transform:rotate(120deg);}.atp-n-1{transform:rotate(-120deg);}.atp-n-cnt-2{transform:rotate(150deg);}.atp-n-2{transform:rotate(-150deg);}.atp-n-cnt-3{transform:rotate(180deg);}.atp-n-3{transform:rotate(-180deg);}.atp-n-cnt-4{transform:rotate(210deg);}.atp-n-4{transform:rotate(-210deg);}.atp-n-cnt-5{transform:rotate(240deg);}.atp-n-5{transform:rotate(-240deg);}.atp-n-cnt-6{transform:rotate(270deg);}.atp-n-6{transform:rotate(-270deg);}.atp-n-cnt-7{transform:rotate(300deg);}.atp-n-7{transform:rotate(-300deg);}.atp-n-cnt-8{transform:rotate(330deg);}.atp-n-8{transform:rotate(-330deg);}.atp-n-cnt-10{transform:rotate(30deg);}.atp-n-10{transform:rotate(-30deg);}.atp-n-cnt-11{transform:rotate(60deg);}.atp-n-11{transform:rotate(-60deg);}.atp-n-cnt-0{transform:rotate(90deg);}.atp-n-0{transform:rotate(-90deg);}.atp-b,.atp-b-spacer{width:1.65em;}.atp-b-spacer{height:1px;}.atp-b{height:1.65em;border-radius:1.65em;}.atp-b-pos{width:0.32em;transition:width 0.1s;height:1px;display:inline-block;}.atp-b-pos-pm{width:2.42em}.atp-clock-btn{padding-top:2em;display:flex;flex-direction:row-reverse;}.atp-time{color:white;font-size:350%;padding:0.3em;text-align:right;}.atp-time .atp-hour,.atp-time .atp-minute{font-size:100%;width:1.3em;background:transparent;border:0;color:white;outline-width:0;opacity:0.7;}.atp-hour.atp-focus,.atp-minute.atp-focus,.atp-am[aria-pressed],.atp-pm[aria-pressed]{opacity:1;}.atp-time .atp-hour{text-align:right;}.atp-ampm{display:inline-block;}.atp-am,.atp-pm{background:transparent;border:0;display:block;text-transform:uppercase;color:white;outline-width:0;font-size:28%;cursor:pointer;opacity:0.7;}button.atp-enforce-font-size{font-size:100%;min-width:0;}.atp-color--primary{background-color:rgb(0,150,136);}.atp-button{background:0 0;border:none;border-radius:2px;color:#000;position:relative;height:36px;margin:0;min-width:64px;padding:0 16px;display:inline-block;font-family:\"Roboto\",\"Helvetica\",\"Arial\",sans-serif;font-size:14px;font-weight:500;text-transform:uppercase;letter-spacing:0;overflow:hidden;will-change:box-shadow;transition:box-shadow .2s cubic-bezier(.4,0,1,1),background-color .2s cubic-bezier(.4,0,.2,1),color .2s cubic-bezier(.4,0,.2,1);outline:none;cursor:pointer;text-decoration:none;text-align:center;line-height:36px;vertical-align:middle;-webkit-tap-highlight-color:transparent;-webkit-tap-highlight-color:rgba(255,255,255,0);}.atp-button--primary{color:rgb(0,150,136);}.atp-modal{position:fixed;top:0;left:0;width:100%;height:100%;background-color:rgba(0, 0, 0, 0.54);display:flex;justify-content:center;align-items:center;}";
var enabled = false;
function enable() {
    if (enabled)
        return;
    enabled = true;
    var el = document.createElement('style');
    el.innerHTML = css;
    var parent = document.head || document.body;
    parent.firstChild ?
        parent.insertBefore(el, parent.firstChild) :
        parent.appendChild(el);
}


// CONCATENATED MODULE: ./index.ts
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "timePicker", function() { return index_timePicker; });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "timePickerModal", function() { return timePickerModal; });
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "timePickerInput", function() { return timePickerInput; });




var index_timePicker = timePicker_create;
var timePickerModal = timePickerModal_create;
var timePickerInput = timePickerInput_create;
// add css to page
enable();



/***/ })
/******/ ]);
});