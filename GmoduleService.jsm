"use strict";

const DEBUG = true;
function debug(s) { dump("-*- GmoduleService component: " + s + "\n"); }


const Cu = Components.utils;
const Cc = Components.classes;
const Ci = Components.interfaces;

this.EXPORTED_SYMBOLS = ["GmoduleService"];

this.GmoduleService =  {	

	init: function () {
		debug('init');
		this.param = 1;
	},

	doAction: function () {
		debug('doAction');
		return this.param;
	}
}

this.GmoduleService.init();