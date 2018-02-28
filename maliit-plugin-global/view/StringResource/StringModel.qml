import QtQuick 2.0

QtObject {
	property var emptyString: PluginProxy.emptyString !== undefined ? PluginProxy.emptyString : ""

	property var symbolTable: {
		"(" : qsTr("Open Parenthesis") + emptyString,
		")" : qsTr("Close Parenthesis") + emptyString,
		"[" : qsTr("Open Brackets") + emptyString,
		"]" : qsTr("Close Brackets") + emptyString,
		"{" : qsTr("Open Curly Brackets") + emptyString,
		"}" : qsTr("Close Curly Brackets") + emptyString,
		"<" : qsTr("Less than") + emptyString,
		">" : qsTr("Greater than") + emptyString,
		"￦" : qsTr("Won") + emptyString,
		"￡" : qsTr("Pound") + emptyString,
		"￥" : qsTr("Yen") + emptyString,
		"€" : qsTr("EURO CURRENCY SIGN") + emptyString,
		"!" : qsTr("EXCLAMATION MARK") + emptyString,
		"@" : qsTr("AT") + emptyString,
		"#" : qsTr("NUMBER SIGN") + emptyString,
		"$" : qsTr("DOLLAR SIGN") + emptyString,
		"%" : qsTr("PERCENT SIGN") + emptyString,
		"^" : qsTr("CIRCUMFLEX") + emptyString,
		"&" : qsTr("AMPERSAND") + emptyString,
		"*" : qsTr("ASTERISK") + emptyString,
		"-" : qsTr("HYPHEN") + emptyString,
		"_" : qsTr("UNDERSCORE") + emptyString,
		"=" : qsTr("EQUALS SIGN") + emptyString,
		"+" : qsTr("PLUS SIGN") + emptyString,
		"\\" : qsTr("BACKSLASH") + emptyString,
		"|" : qsTr("VERTICAL BAR") + emptyString,
		";" : qsTr("SEMICOLON") + emptyString,
		":" : qsTr("COLON") + emptyString,
		"'" : qsTr("APOSTROPHE") + emptyString,
		"\"" : qsTr("QUOTATION MARK") + emptyString,
		"," : qsTr("COMMA") + emptyString,
		"." : qsTr("FULL STOP") + emptyString,
		"/" : qsTr("SLASH") + emptyString,
		"?" : qsTr("QUESTION MARK") + emptyString,
		"§" : qsTr("SECTION SIGN") + emptyString,
		"¿" : qsTr("INVERTED QUESTION MARK") + emptyString,
		"`" : qsTr("GRAVE ACCENT") + emptyString,
		"~" : qsTr("TILDE") + emptyString,
	}

	property var localeInfoTable: {
		"sq" : qsTr("Albanian") + emptyString,
		"ar" : qsTr("Arabic") + emptyString,
		"bs" : qsTr("Bosnian") + emptyString,
		"bg" : qsTr("Bulgarian") + emptyString,
		"hr" : qsTr("Croatian") + emptyString,
		"cs" : qsTr("Czech") + emptyString,
		"da" : qsTr("Danish") + emptyString,
		"nl" : qsTr("Dutch") + emptyString,
		"en" : qsTr("English") + emptyString,
		"et" : qsTr("Estonian") + emptyString,
		"fi" : qsTr("Finnish") + emptyString,
		"fr" : qsTr("French") + emptyString,
		"ga" : qsTr("Gaelic") + emptyString,
		"de" : qsTr("German") + emptyString,
		"el" : qsTr("Greek") + emptyString,
		"he" : qsTr("Hebrew") + emptyString,
		"hi" : qsTr("Hindi") + emptyString,
		"hu" : qsTr("Hungarian") + emptyString,
		"id" : qsTr("Indonesian") + emptyString,
		"ga" : qsTr("Irish") + emptyString,
		"it" : qsTr("Italian") + emptyString,
		"kk" : qsTr("Kazakh") + emptyString,
		"ko" : qsTr("Korean") + emptyString,
		"ku" : qsTr("Kurdish") + emptyString,
		"lv" : qsTr("Latvian") + emptyString,
		"lt" : qsTr("Lithuanian") + emptyString,
		"mk" : qsTr("Macedonian") + emptyString,
		"ms" : qsTr("Malay") + emptyString,
		"mi" : qsTr("Maori") + emptyString,
		"mn" : qsTr("Mongolian") + emptyString,
		"nb" : qsTr("Norwegian") + emptyString,
		"fa" : qsTr("Persian") + emptyString,
		"pl" : qsTr("Polish") + emptyString,
		"pt" : qsTr("Portuguese") + emptyString,
		"ro" : qsTr("Romanian") + emptyString,
		"ru" : qsTr("Russian") + emptyString,
		"sr" : qsTr("Serbian") + emptyString,
		"sk" : qsTr("Slovak") + emptyString,
		"sl" : qsTr("Slovenian") + emptyString,
		"es" : qsTr("Spanish") + emptyString,
		"sv" : qsTr("Swedish") + emptyString,
		"th" : qsTr("Thai") + emptyString,
		"tr" : qsTr("Turkish") + emptyString,
		"uk" : qsTr("Ukrainian") + emptyString,
		"uz" : qsTr("Uzbek") + emptyString,
		"vi" : qsTr("Vietnamese") + emptyString,
		"ja" : qsTr("Japanese") + emptyString,
		"zh" : qsTr("Chinese") + emptyString
	}

	function getStringLangCode(langCode) {
		if (localeInfoTable[langCode]) {
			return localeInfoTable[langCode]
		};
		return "";
	}

	function getPronounceByChar(character) {
		return symbolTable[character] || character;
	}
}

