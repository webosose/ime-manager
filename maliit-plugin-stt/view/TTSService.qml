import QtQuick 2.2
import WebOSServices 1.0

Item {
    id: root

    property string _appId: "com.webos.service.ime.stt"

    property bool audioGuidanceEnable : false

    function speak(text, language) {
        var param = {
            "text": text.replace(/\"/g,"\\\""),
            "clear": true,
            "mode": "searchApp",
            "language": language
        };
        speak.callService(param);
    }

    function speakByAudioGuidance(text, language, clear) {
        printWarningLog("[Audio Guidance] " + text);
        if(!audioGuidanceEnable||text==="") return;
        var param = {
            "text": text.replace(/\"/g,"\\\""),
            "clear": true,
            "language": language
        };
        if (clear !== undefined)
            param.clear = clear;

        speak.callService(param);
    }
    function speakCancel() {
        speak.cancel();
    }
    function callGetSystemSettings(){
        var param =  {"subscribe": true, "keys" : ["audioGuidance"],"category": "option"}
        getSystemSettings.callService(param)
    }

    Service {
        id: speak
        appId: root._appId
        service: "com.webos.service.tts"
        method: "speak"
//        onCallSuccess: responseSpeak(response)
//        onCallFailure: responseSpeakFailure(response)
    }

    Service {
        id: getSystemSettings
        appId: root._appId
        service: "com.webos.settingsservice"
        method: "getSystemSettings"
        onCallSuccess: {
            if(response.returnValue && response.settings.audioGuidance === "on")
                root.audioGuidanceEnable = true
            else
                root.audioGuidanceEnable = false
        }
        onCallFailure: {
            root.audioGuidanceEnable = false
        }
    }
}
