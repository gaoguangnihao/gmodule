/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

"use strict";

const DEBUG = true;
function debug(s) { dump("-*- GmoduleManager: " + s + "\n"); }

const Cc = Components.classes;
const Ci = Components.interfaces;
const Cu = Components.utils;

Cu.import("resource://gre/modules/XPCOMUtils.jsm");
Cu.import("resource://gre/modules/Services.jsm");

XPCOMUtils.defineLazyModuleGetter(this, "GmoduleService",
                                  "resource://gre/modules/GmoduleService.jsm");

function GmoduleManager() {};

GmoduleManager.prototype = {
	init: function() {
		debug('init enter');

		// test jsm
		var r = GmoduleService.doAction();
		debug('GmoduleService doAction return ' + r);
	},

	classID: Components.ID("{8ce7473f-b77d-4130-8b33-eaef78f14841}"),
	contractID: "@mozilla.org/gmoduleManager;1",
	QueryInterface: XPCOMUtils.generateQI([Ci.nsISupports,Ci.nsIGmoduleManager]),
}

this.NSGetFactory = XPCOMUtils.generateNSGetFactory([GmoduleManager]);