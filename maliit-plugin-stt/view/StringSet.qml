import QtQuick 2.0

QtObject {
    id: root

    property var strings: {
        "OK": qsTr("OK") + PluginProxy.emptyString, // i18n this is used for ok button
        "CANCEL": qsTr("CANCEL") + PluginProxy.emptyString, // i18n this is used for cancel button
        "YES": qsTr("YES") + PluginProxy.emptyString,   // i18n text on button
        "NO": qsTr("NO") + PluginProxy.emptyString,   // i18n text on button
        "checked": qsTr("checked") + PluginProxy.emptyString,  // i18n text for tts
        "unchecked": qsTr("unchecked") + PluginProxy.emptyString,    // i18n text for tts
        "scroll up": qsTr("scroll up")  + PluginProxy.emptyString,   // i18n scroll bar up button string for tts
        "scroll down": qsTr("scroll down") + PluginProxy.emptyString, // i18n scroll bar up button string for tts
        "up": qsTr("up") + PluginProxy.emptyString, // i18n button name up
        "down": qsTr("down") + PluginProxy.emptyString, // i18n button name down
        "Do you want to go to \"Network Settings\" now to check the connection?": qsTr("Do you want to go to \"Network Settings\" now to check the connection?") + PluginProxy.emptyString, // i18n this is content for network disconnected alert popup to make user go to network setting
        "Voice is not recognized. Try again.": qsTr("Voice is not recognized. Try again.") + PluginProxy.emptyString, // i18n this is message for unrecognized voice error.
        "Do you want to go to \"Network Settings\" now to set up the network?": qsTr("Do you want to go to \"Network Settings\" now to set up the network?") + PluginProxy.emptyString, // i18n this is content for network not set up alert popup to make user go to network setting
        "Speak to input text.": qsTr("Speak to input text.") + PluginProxy.emptyString, // i18n This sentence appears when user tries to input text by voice recognition.
        " (": qsTr(" (") + PluginProxy.emptyString, // i18n left pahrenheit
        ")": qsTr(")") + PluginProxy.emptyString, // i18n right pahrenheit
        "VOICE RECOGNITION RESULTS": qsTr("VOICE RECOGNITION RESULTS") + PluginProxy.emptyString, // i18n this is title for voice recognition result
        "Voice recognition server is not responding. Try again.": qsTr("Voice recognition server is not responding. Try again.") + PluginProxy.emptyString, // i18n this is error message for server side error.
        "Turn on Bluetooth and then speak to Magic remote for voice recognition.": qsTr("Turn on Bluetooth and then speak to Magic remote for voice recognition.") + PluginProxy.emptyString, // i18n this is error message that user need to turn on bluetooth function on network setting.
        "You need to use LG Magic Remote to use voice recognition.": qsTr("You need to use LG Magic Remote to use voice recognition.") + PluginProxy.emptyString, // i18n this is message that user need to use magic remote to use STT function.
        "To use voice recognition with the Magic Remote that you are currently using, please try again from the other TV.": qsTr("To use voice recognition with the Magic Remote that you are currently using, please try again from the other TV.") + PluginProxy.emptyString, // i18n This is error message for unpaired mrcu on TwinMode
        "Loading": qsTr("Loading") + PluginProxy.emptyString, // i18n for TTS to process search
        "button": qsTr("button") + PluginProxy.emptyString, // i18n for TTS with button
        "SELECT LANGUAGE": qsTr("SELECT LANGUAGE") + PluginProxy.emptyString, // i18n This is title for voice recognition language select popup.
        "Red Button": qsTr("Red Button") + PluginProxy.emptyString,  // i18n remocon button red
        "Press %1%2 to change language.": qsTr("Press %1%2 to change language.") + PluginProxy.emptyString,  // i18n - This string is guide string to make user to press red button on remote controller if he wants to change STT(Speak To Text)Language. For example, it can be translated to Korean like this "ì–¸ì–´ ë³€ê²½ì„ ì›í•˜ì‹œë©´ %1%2 ì„ ëˆŒëŸ¬ì£¼ì„¸ìš”". Thus, %1 is object in this sentence, and some html code is in %2.
        "RETRY": qsTr("RETRY") + PluginProxy.emptyString,  // i18n Button text means retrying voice recognition.
        "Network server is not Responding. Try again.": qsTr("Network server is not Responding. Try again.") + PluginProxy.emptyString, // i18n error sentence
        "Voice is not recognized. Keep your distance from the remote control and speak again.": qsTr("Voice is not recognized. Keep your distance from the remote control and speak again.") + PluginProxy.emptyString, // i18n error sentence
        "Try again after update is complete.": qsTr("Try again after update is complete.") + PluginProxy.emptyString,  // i18n error sentence
        "Speech to text": qsTr("Speech to text") + PluginProxy.emptyString, // i18n text for tts
// Add
        "Mic connection is unstable.": qsTr("Mic connection is unstable.") + PluginProxy.emptyString,  // i18n error sentence
// Not use
//        "Network Disconnected": qsTr("Network Disconnected") + PluginProxy.emptyString, // i18n this is title for network disconnected alert popup to make user go to network setting
//        "Network not set up": qsTr("Network not set up") + PluginProxy.emptyString, // i18n this is title for network not set up alert popup to make user go to network setting
//        "You must register Magic remote to TV to use voice recognition.": qsTr("You must register Magic remote to TV to use voice recognition.") + PluginProxy.emptyString, // i18n this is error message that user need to pair magic remote first to use STT function.
// Not use & translate
//        "Voice language and country location do not match. Voice service will run search function only.": qsTr("Voice language and country location do not match. Voice service will run search function only.") + PluginProxy.emptyString, // i18n error sentence
    }

}
