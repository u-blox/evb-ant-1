
/*
* Copyright 2023 u-blox
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <httpsrv_fs.h>

extern const HTTPSRV_FS_DIR_ENTRY httpsrv_fs_data[];
const char httpsrv_fs_webpage_my_index_html[] = "<html>\n<head>\n    <meta charset=\"ASCII\">\n    <title>EVB-ANT-1</t"
                                                "itle>\n    <link rel=\"icon\" type=\"image\" href=\"/favicon-16x16.pn"
                                                "g\">\n    <link rel=\"stylesheet\" href=\"style.css\">\n    <link rel"
                                                "=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-aw"
                                                "esome/5.13.0/css/all.min.css\">\n\t<script src=\"evbConf.js\"></scrip"
                                                "t> \n</head>\n<body>\n\n\n<h1>EVB-ANT-1</h1>\n<h2>Configuration</h2>"
                                                "\n\n\n\n<div id=\"configurationArea\">\n\t\n\t<h3> WiFi Setup</h3>\n"
                                                "\t<label class=\"NameColumn\" for=\"wifiEnabled\">Enabled:</label>\n"
                                                "\t<input class=\"ValueColumn\" type=\"checkbox\" id=\"wifiEnabled\" n"
                                                "ame=\"wifiEnabled\"><br><br>\n\t<label class=\"NameColumn\" for=\"ssi"
                                                "d\">SSID:</label>\n\t<input class=\"ValueColumn\" type=\"text\" id=\""
                                                "ssid\" name=\"ssid\"><br><br>\n\t<label class=\"NameColumn\" for=\"pa"
                                                "ssw\">Password:</label>\n\t<input class=\"ValueColumn\" type=\"passwo"
                                                "rd\" id=\"passw\" name=\"passw\">\n\t<i class=\"far fa-eye\" id=\"tog"
                                                "glePassw\" onclick=\"toggleShowPassword()\"></i><br><br>\n\t<label cl"
                                                "ass=\"NameColumn\" for=\"wifiip\">IP:</label>\n\t<input class=\"Value"
                                                "Column\" type=\"text\" id=\"wifiip\" name=\"wifiip\"><br><br>\n\t<lab"
                                                "el class=\"NameColumn\" for=\"wifimask\">Subnet mask:</label>\n\t<inp"
                                                "ut class=\"ValueColumn\" type=\"text\" id=\"wifimask\" name=\"wifimas"
                                                "k\"><br><br>\n\t<label class=\"NameColumn\" for=\"wifigw\">Default Ga"
                                                "teway:</label>\n\t<input class=\"ValueColumn\" type=\"text\" id=\"wif"
                                                "igw\" name=\"wifigw\"><br><br>\n\t<label class=\"NameColumn\" for=\"w"
                                                "ifidns1\">DNS Server 1:</label>\n\t<input class=\"ValueColumn\" type="
                                                "\"text\" id=\"wifidns1\" name=\"wifidns1\"><br><br>\n\t<label class="
                                                "\"NameColumn\" for=\"wifidns2\">DNS Server 2:</label>\n\t<input class"
                                                "=\"ValueColumn\" type=\"text\" id=\"wifidns2\" name=\"wifidns2\"><br>"
                                                "<br>\n\t<label class=\"NameColumn\" for=\"wifiuseDHCP\">Use DHCP:</la"
                                                "bel>\n\t<input class=\"ValueColumn\" type=\"checkbox\" id=\"wifiuseDH"
                                                "CP\" name=\"wifiuseDHCP\" onclick=\"checkDHCPToggles()\"><br><br>\n\t"
                                                "<label class=\"NameColumn\" for=\"wifirssi\">Signal RSSI:</label>\n\t"
                                                "<label class=\"ValueColumn\" id=\"wifirssi\"> - </label><br><br>\n\t<"
                                                "hr>\n\t<h3> Ethernet Setup</h3>\n\t<label class=\"NameColumn\" for=\""
                                                "enetEnabled\">Enabled:</label>\n\t<input class=\"ValueColumn\" type="
                                                "\"checkbox\" id=\"enetEnabled\" name=\"enetEnabled\"><br><br>\n\t<lab"
                                                "el class=\"NameColumn\" for=\"enetip\">IP:</label>\n\t<input class=\""
                                                "ValueColumn\" type=\"text\" id=\"enetip\" name=\"enetip\"><br><br>\n"
                                                "\t<label class=\"NameColumn\" for=\"enetmask\">Subnet mask:</label>\n"
                                                "\t<input class=\"ValueColumn\" type=\"text\" id=\"enetmask\" name=\"e"
                                                "netmask\"><br><br>\n\t<label class=\"NameColumn\" for=\"enetgw\">Defa"
                                                "ult Gateway:</label>\n\t<input class=\"ValueColumn\" type=\"text\" id"
                                                "=\"enetgw\" name=\"enetgw\"><br><br>\n\t<label class=\"NameColumn\" f"
                                                "or=\"enetdns1\">DNS Server 1:</label>\n\t<input class=\"ValueColumn\""
                                                " type=\"text\" id=\"enetdns1\" name=\"enetdns1\"><br><br>\n\t<label c"
                                                "lass=\"NameColumn\" for=\"enetdns2\">DNS Server 2:</label>\n\t<input "
                                                "class=\"ValueColumn\" type=\"text\" id=\"enetdns2\" name=\"enetdns2\""
                                                "><br><br>\n\t<label class=\"NameColumn\" for=\"enetuseDHCP\">Use DHCP"
                                                ":</label>\n\t<input class=\"ValueColumn\" type=\"checkbox\" id=\"enet"
                                                "useDHCP\" name=\"enetuseDHCP\" onclick=\"checkDHCPToggles()\"><br><br"
                                                ">\n\t<hr>\n\t<h3> Position Engine Setup</h3>\n\t<label class=\"NameCo"
                                                "lumn\" for=\"posengip\">IP / Hostname:</label>\n\t<input class=\"Valu"
                                                "eColumn\" type=\"text\" id=\"posengip\" name=\"posengip\"><br><br>\n"
                                                "\t<label class=\"NameColumn\" for=\"posengport\">Port:</label>\n\t<in"
                                                "put class=\"ValueColumn\" type=\"text\" id=\"posengport\" name=\"pose"
                                                "ngport\"><br><br>\n\t<hr>\n\t<h3> Anchor Point Setup</h3>\n\t<label c"
                                                "lass=\"NameColumn\" for=\"activeNINA\">Active NINA module:</label>\n"
                                                "\t<select class=\"ValueColumn\" name=\"activeNINA\" id=\"activeNINA\""
                                                ">\n\t\t<option value=\"antb10\">ANT-B10</option>\n\t\t<option value="
                                                "\"onboard\">Onboard NINA module</option>\n\t</select><br><br>\n\t<lab"
                                                "el class=\"NameColumn\">NINA Buttons:</label>\n\t<div class=\"ValueCo"
                                                "lumn\">\n\t\t<button class=\"NinaButtons\" onclick=\"doNinaReset()\">"
                                                "Reset</button>\n\t\t<button class=\"NinaButtons\" onclick=\"doNinaSw1"
                                                "()\">Switch 1</button>\n\t\t<button class=\"NinaButtons\" onclick=\"d"
                                                "oNinaSw2()\">Switch 2</button>\n\t</div><br><br>\n\n\t<label class=\""
                                                "NameColumn\">Send AT Command:</label>\n\t<div class=\"ValueColumn\">"
                                                "\n\t\t<input type=\"text\" id=\"atcommand\" name=\"atcommand\">\n\t\t"
                                                "<button id=\"SendATButton\" onclick=\"doAtSend()\">Send</button>\n\t<"
                                                "/div>\n\t<br><br>\n\t<hr>\n\n\t<div id=\"buttonsDiv\">\n\t\t<button i"
                                                "d=\"submitButton\" onclick=\"doSubmitConf()\">Submit</button>\n\t\t<b"
                                                "utton id=\"readButton\" onclick=\"doReadConf()\">Read</button>\n\t</d"
                                                "iv>\n\t\n\t<label id=\"firmwareVersionLabel\">F/W version: </label>\n"
                                                "\n</div>\n\n<div id=\"UptimeInfo\">\n\t<label>Uptime:</label>\n\t<div"
                                                " id=\"time\" class=\"rtc_data\">00:00:00</div>\n\t<button id=\"reboot"
                                                "Button\" onclick=\"doReboot()\">Reboot</button> \n</div>\n\n\n</body>"
                                                "</html>";

const char httpsrv_fs_webpage_evb_conf_js[] = "function checkDHCPToggles(){\n\tlet enetDHCP = document.getElementByI"
                                              "d(\"enetuseDHCP\").checked;\n\tlet wifiDHCP = document.getElementById"
                                              "(\"wifiuseDHCP\").checked;\n\n\tdocument.getElementById(\"enetip\").d"
                                              "isabled = enetDHCP;\n\tdocument.getElementById(\"enetmask\").disabled"
                                              " = enetDHCP;\n\tdocument.getElementById(\"enetgw\").disabled = enetDH"
                                              "CP;\n\tdocument.getElementById(\"enetdns1\").disabled = enetDHCP;\n\t"
                                              "document.getElementById(\"enetdns2\").disabled = enetDHCP;\n\n\tdocum"
                                              "ent.getElementById(\"wifiip\").disabled = wifiDHCP;\n\tdocument.getEl"
                                              "ementById(\"wifimask\").disabled = wifiDHCP;\n\tdocument.getElementBy"
                                              "Id(\"wifigw\").disabled = wifiDHCP;\n\tdocument.getElementById(\"wifi"
                                              "dns1\").disabled = wifiDHCP;\n\tdocument.getElementById(\"wifidns2\")"
                                              ".disabled = wifiDHCP;\n}\n\nfunction toggleShowPassword(){\n\tlet inp"
                                              "ut = document.getElementById(\"passw\");\n\tlet icon = document.getEl"
                                              "ementById(\"togglePassw\");\n\tif (input.type === \"password\"){\n\t"
                                              "\tinput.type = \"text\";\n\t\ticon.className = \"far fa-eye-slash\";"
                                              "\n\t} else {\n\t\tinput.type = \"password\";\n\t\ticon.className = \""
                                              "far fa-eye\";\n\t}\n}\n\nfunction doReboot(){\n\tconst xhttp = new XM"
                                              "LHttpRequest();\n\txhttp.open(\"GET\", \"reboot.cgi\");\n\txhttp.send"
                                              "();\n}\t\n\nfunction doNinaReset(){\n\tconst xhttp = new XMLHttpReque"
                                              "st();\n\txhttp.open(\"GET\", \"nina_reset.cgi\");\n\txhttp.send();\n}"
                                              "\t\n\nfunction doNinaSw1(){\n\tconst xhttp = new XMLHttpRequest();\n"
                                              "\txhttp.open(\"GET\", \"nina_sw1.cgi\");\n\txhttp.send();\n}\n\nfunct"
                                              "ion doNinaSw2(){\n\tconst xhttp = new XMLHttpRequest();\n\txhttp.open"
                                              "(\"GET\", \"nina_sw2.cgi\");\n\txhttp.send();\n}\t\n\nfunction getUpt"
                                              "imeData(){\n\tconst xhttp = new XMLHttpRequest();\n\txhttp.onreadysta"
                                              "techange = parseRTCData;\n\txhttp.open(\"GET\", \"rtcdata.cgi\");\n\t"
                                              "xhttp.send();\n}\n\nfunction parseRTCData(){\n\tif (this.readyState ="
                                              "== XMLHttpRequest.DONE) {\n      \tif (this.status === 200) {\n      "
                                              "\t\tlet response = this.responseText.split(\"\\n\");\n      \t\tdocum"
                                              "ent.getElementById(\"time\").innerHTML = leftPadIfNeeded(response[0])"
                                              " + \":\" + leftPadIfNeeded(response[1]) + \":\" + leftPadIfNeeded(res"
                                              "ponse[2]);\n      \t\tsetTimeout(getUptimeData, 1000);\n      \t}\n  "
                                              "\t}\n}\n\nfunction leftPadIfNeeded(input){\n\treturn (input < 10)\? "
                                              "\'0\' + input : input;\n}\n\nfunction getFirmwareVersion(){\n\tconst "
                                              "xhttp = new XMLHttpRequest();\n\txhttp.onreadystatechange = handleFWV"
                                              "ersion;\n\txhttp.open(\"GET\", \"get_version.cgi\");\n\txhttp.send();"
                                              "\n}\n\nfunction handleFWVersion(){\n\tif (this.readyState === XMLHttp"
                                              "Request.DONE) {\n      \tif (this.status === 200) {\n      \t\tdocume"
                                              "nt.getElementById(\"firmwareVersionLabel\").innerHTML += this.respons"
                                              "eText;\n      \t}\n  \t}\t\n}\n\nfunction doSubmitConf() {\n\n\tlet c"
                                              "ontent = {};\n\tcontent.wifien = document.getElementById(\"wifiEnable"
                                              "d\").checked;\n\tcontent.ssid = document.getElementById(\"ssid\").val"
                                              "ue;\n\tcontent.password = document.getElementById(\"passw\").value;\n"
                                              "\tcontent.enetip = document.getElementById(\"enetip\").value;\n\tcont"
                                              "ent.enetmask = document.getElementById(\"enetmask\").value;\n\tconten"
                                              "t.enetgw = document.getElementById(\"enetgw\").value;\n\tcontent.enet"
                                              "dns1 = document.getElementById(\"enetdns1\").value;\n\tcontent.enetdn"
                                              "s2 = document.getElementById(\"enetdns2\").value;\n\tcontent.enetuseD"
                                              "HCP = document.getElementById(\"enetuseDHCP\").checked;\n\tcontent.po"
                                              "sengip = document.getElementById(\"posengip\").value;\n\tcontent.pose"
                                              "ngport = document.getElementById(\"posengport\").value;\n\tcontent.wi"
                                              "fiip = document.getElementById(\"wifiip\").value;\n\tcontent.wifimask"
                                              " = document.getElementById(\"wifimask\").value;\n\tcontent.wifigw = d"
                                              "ocument.getElementById(\"wifigw\").value;\n\tcontent.wifidns1 = docum"
                                              "ent.getElementById(\"wifidns1\").value;\n\tcontent.wifidns2 = documen"
                                              "t.getElementById(\"wifidns2\").value;\n\tcontent.wifiuseDHCP = docume"
                                              "nt.getElementById(\"wifiuseDHCP\").checked;\n\tcontent.eneten = docum"
                                              "ent.getElementById(\"enetEnabled\").checked;\n\tcontent.onboardNina ="
                                              " (document.getElementById(\"activeNINA\").value === \"onboard\");\n\n"
                                              "\tconst xhttp = new XMLHttpRequest();\n\txhttp.open(\"POST\", \"post."
                                              "cgi\");\n\txhttp.setRequestHeader(\"Content-type\", \"application/x-w"
                                              "ww-form-urlencoded\");\n\txhttp.send(\"post_input=\" + JSON.stringify"
                                              "(content));\n}\n\n\nfunction doReadConf(){\n\tconst xhttp = new XMLHt"
                                              "tpRequest();\n\txhttp.onreadystatechange = parseConfResponse;\n\txhtt"
                                              "p.open(\"GET\", \"get.cgi\");\n\txhttp.send();\n}\n\nfunction parseCo"
                                              "nfResponse() {\n    if (this.readyState === XMLHttpRequest.DONE) {\n "
                                              "     if (this.status === 200) {\n      \tlet response = JSON.parse(th"
                                              "is.responseText);\n\n      \tdocument.getElementById(\"wifiEnabled\")"
                                              ".checked = response.wifien;\n    \tdocument.getElementById(\"ssid\")."
                                              "value = response.ssid;\n\t\tdocument.getElementById(\"passw\").value "
                                              "= response.password;\n\t\tdocument.getElementById(\"enetip\").value ="
                                              " response.enetip;\n\t\tdocument.getElementById(\"enetmask\").value = "
                                              "response.enetmask;\n\t\tdocument.getElementById(\"enetgw\").value = r"
                                              "esponse.enetgw;\n\t\tdocument.getElementById(\"enetdns1\").value = re"
                                              "sponse.enetdns1;\n\t\tdocument.getElementById(\"enetdns2\").value = r"
                                              "esponse.enetdns2;\n\t\tdocument.getElementById(\"enetuseDHCP\").check"
                                              "ed = response.enetuseDHCP;\n\t\tdocument.getElementById(\"posengip\")"
                                              ".value = response.posengip;\n\t\tdocument.getElementById(\"posengport"
                                              "\").value = response.posengport;\n\t\tdocument.getElementById(\"wifii"
                                              "p\").value = response.wifiip;\n\t\tdocument.getElementById(\"wifimask"
                                              "\").value = response.wifimask;\n\t\tdocument.getElementById(\"wifigw"
                                              "\").value = response.wifigw;\n\t\tdocument.getElementById(\"wifidns1"
                                              "\").value = response.wifidns1;\n\t\tdocument.getElementById(\"wifidns"
                                              "2\").value = response.wifidns2;\n\t\tdocument.getElementById(\"wifius"
                                              "eDHCP\").checked = response.wifiuseDHCP;\n\t\tdocument.getElementById"
                                              "(\"enetEnabled\").checked = response.eneten;\n\t\tdocument.getElement"
                                              "ById(\"activeNINA\").value = (response.onboardNina) \? \"onboard\" : "
                                              "\"antb10\";\n\t\tdocument.getElementById(\"wifirssi\").innerText = (r"
                                              "esponse.wifirssi > -256) \? response.wifirssi : \" - \";\n\n\t\tcheck"
                                              "DHCPToggles();\n\n      } else {\n        alert(\'There was a problem"
                                              " with the request.\');\n      }\n    }\n}\n\nfunction doAtSend() {\n"
                                              "\tconst xhttp = new XMLHttpRequest();\n\txhttp.open(\"POST\", \"at_cm"
                                              "d.cgi\");\n\txhttp.setRequestHeader(\"Content-type\", \"application/x"
                                              "-www-form-urlencoded\");\n\txhttp.send(\"command=\" + document.getEle"
                                              "mentById(\"atcommand\").value + \"\\r\");\n\tconsole.log(\"Sent\", do"
                                              "cument.getElementById(\"atcommand\").value + \"\\r\")\n}\n\nfunction "
                                              "windowOnLoad() {\n  \tgetUptimeData();\n  \tdoReadConf();\n\tgetFirmw"
                                              "areVersion();\n}\n\nwindow.onload = windowOnLoad;\n";

const char httpsrv_fs_webpage_my_style_css[] = "body{\n    text-align: center;\n    background-color: white;\n    fon"
                                               "t-family: Helvetica, sans-serif;\n}\n\n#configurationArea {\n\tmargin"
                                               ": auto;\n\twidth: 400px;\n\tpadding: 30px;\n\tborder: 1px solid black"
                                               ";\n\tborder-radius: 10px;\n\ttext-align: left;\n}\n\n#configurationAr"
                                               "ea h3{\n\ttext-align: center;\n}\n\n.NameColumn {\n\twidth: 150px;\n"
                                               "\tfloat: left;\n\ttext-align: right;\n}\n\n.ValueColumn {\n\tmargin-l"
                                               "eft: 20px;\n\tdisplay: inline-block;\n}\n\n#buttonsDiv {\n\ttext-alig"
                                               "n: center;\n\tpadding-top: 20px;\n}\n\n#buttonsDiv button {\n\tmargin"
                                               ": 0 10px 0 10px;\n}\n\n#uptimeInfo{\n\tmargin: 20px;\n}\n\n.rtc_data{"
                                               "\n\tdisplay: inline-block;\n\tmargin: 0 10px 0 10px;\n}\n\n#togglePas"
                                               "sw{\n\tmargin-left: -25px; \n\tfont-size: 12px; \n\tcursor: pointer;"
                                               "\n}\n\n#firmwareVersionLabel{\n\tfloat: right;\n\tfont-size: 10px;\n"
                                               "\tmargin-top: 12px;\n\tmargin-right: -14px;\n}";

static const unsigned char httpsrv_fs_webpage_my_favicon[] = {
    0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,
    0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x08, 0x03, 0x00, 0x00, 0x00, 0x28, 0x2D, 0x0F,
    0x53, 0x00, 0x00, 0x00, 0x04, 0x67, 0x41, 0x4D, 0x41, 0x00, 0x00, 0xB1, 0x8F, 0x0B, 0xFC, 0x61,
    0x05, 0x00, 0x00, 0x00, 0x20, 0x63, 0x48, 0x52, 0x4D, 0x00, 0x00, 0x7A, 0x26, 0x00, 0x00, 0x80,
    0x84, 0x00, 0x00, 0xFA, 0x00, 0x00, 0x00, 0x80, 0xE8, 0x00, 0x00, 0x75, 0x30, 0x00, 0x00, 0xEA,
    0x60, 0x00, 0x00, 0x3A, 0x98, 0x00, 0x00, 0x17, 0x70, 0x9C, 0xBA, 0x51, 0x3C, 0x00, 0x00, 0x00,
    0xF9, 0x50, 0x4C, 0x54, 0x45, 0x00, 0x00, 0x00, 0xEA, 0x1D, 0x25, 0xEB, 0x1A, 0x24, 0xCF, 0x00,
    0x00, 0xEA, 0x1D, 0x25, 0xEA, 0x1D, 0x25, 0xEA, 0x1D, 0x25, 0xEA, 0x1D, 0x25, 0xEA, 0x1D, 0x25,
    0xEA, 0x1D, 0x25, 0xEA, 0x1D, 0x25, 0xEA, 0x1D, 0x25, 0xEA, 0x1D, 0x25, 0xEA, 0x1D, 0x25, 0xEA,
    0x1D, 0x25, 0xEA, 0x1C, 0x24, 0xEA, 0x1D, 0x25, 0xEB, 0x27, 0x2E, 0xEC, 0x36, 0x3D, 0xED, 0x39,
    0x40, 0xED, 0x42, 0x49, 0xFD, 0xE9, 0xEA, 0xF2, 0x70, 0x75, 0xFF, 0xFE, 0xFE, 0xFE, 0xF5, 0xF5,
    0xF3, 0x79, 0x7C, 0xFF, 0xFB, 0xFB, 0xFF, 0xFF, 0xFF, 0xEA, 0x19, 0x21, 0xEA, 0x18, 0x20, 0xE8,
    0x12, 0x19, 0xEA, 0x1D, 0x25, 0xEA, 0x1B, 0x23, 0xEA, 0x19, 0x21, 0xEA, 0x1C, 0x24, 0xED, 0x3C,
    0x42, 0xF1, 0x64, 0x68, 0xEC, 0x31, 0x37, 0xEB, 0x27, 0x2F, 0xF9, 0xBF, 0xC0, 0xFF, 0xFF, 0xFF,
    0xF6, 0x9D, 0x9F, 0xEA, 0x1E, 0x25, 0xEB, 0x28, 0x2F, 0xEA, 0x1A, 0x22, 0xED, 0x3C, 0x43, 0xF1,
    0x64, 0x69, 0xEC, 0x2F, 0x36, 0xED, 0x3B, 0x42, 0xF2, 0x6F, 0x73, 0xEE, 0x43, 0x49, 0xEB, 0x23,
    0x2A, 0xF0, 0x60, 0x65, 0xF0, 0x62, 0x67, 0xEA, 0x18, 0x20, 0xF2, 0x74, 0x78, 0xF4, 0x86, 0x8A,
    0xEA, 0x18, 0x21, 0xEB, 0x2D, 0x34, 0xFB, 0xD7, 0xD8, 0xFC, 0xDE, 0xDF, 0xF4, 0x86, 0x8B, 0xFB,
    0xD7, 0xD9, 0xFC, 0xDF, 0xE0, 0xF4, 0x88, 0x8C, 0xE9, 0x15, 0x1E, 0xEC, 0x2E, 0x35, 0xFC, 0xDB,
    0xDC, 0xF1, 0x6A, 0x6E, 0xF9, 0xC3, 0xC4, 0xEF, 0x53, 0x58, 0xF3, 0x83, 0x86, 0xFE, 0xF7, 0xF7,
    0xED, 0x39, 0x3F, 0xFB, 0xD0, 0xD1, 0xFE, 0xF8, 0xF8, 0xFD, 0xEC, 0xEC, 0xFE, 0xF2, 0xF1, 0xED,
    0x3D, 0x43, 0xF3, 0x7D, 0x80, 0xF4, 0x88, 0x8A, 0xEF, 0x55, 0x5A, 0xEA, 0x19, 0x22, 0x83, 0xED,
    0x5E, 0xFF, 0x00, 0x00, 0x00, 0x1F, 0x74, 0x52, 0x4E, 0x53, 0x00, 0x00, 0x00, 0x00, 0x07, 0x4B,
    0xAA, 0xE6, 0xFC, 0x1A, 0x95, 0xF0, 0xB3, 0x4C, 0xEE, 0xAA, 0xE5, 0xE5, 0xFC, 0xE5, 0xAA, 0xF0,
    0x4D, 0xD8, 0x1D, 0xB9, 0x50, 0x0A, 0xEF, 0x95, 0x1A, 0x0C, 0x7B, 0xE7, 0x87, 0x00, 0x00, 0x00,
    0x01, 0x62, 0x4B, 0x47, 0x44, 0x1B, 0x02, 0x60, 0xD4, 0xA4, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48,
    0x59, 0x73, 0x00, 0x00, 0x0B, 0x12, 0x00, 0x00, 0x0B, 0x12, 0x01, 0xD2, 0xDD, 0x7E, 0xFC, 0x00,
    0x00, 0x00, 0x07, 0x74, 0x49, 0x4D, 0x45, 0x07, 0xE2, 0x09, 0x12, 0x11, 0x05, 0x00, 0x00, 0xCB,
    0xD0, 0x4E, 0x00, 0x00, 0x00, 0xCA, 0x49, 0x44, 0x41, 0x54, 0x18, 0xD3, 0x5D, 0xCF, 0xD9, 0x52,
    0xC2, 0x30, 0x14, 0x06, 0xE0, 0x13, 0xE8, 0xDE, 0x52, 0xA1, 0x28, 0x8B, 0x0A, 0x27, 0x8D, 0x28,
    0x51, 0x2B, 0x20, 0xA0, 0xB5, 0xA5, 0x20, 0x6E, 0xB8, 0xA1, 0x02, 0xEF, 0xFF, 0x30, 0x24, 0x29,
    0x33, 0xCC, 0x98, 0xBB, 0x7C, 0xF3, 0x9F, 0x0D, 0x00, 0x88, 0xA6, 0x1B, 0xA6, 0x65, 0x99, 0x86,
    0xAE, 0x11, 0x10, 0x5F, 0x62, 0x3B, 0x2E, 0xAA, 0xE7, 0x3A, 0x36, 0x21, 0x40, 0x6C, 0x0F, 0x91,
    0x86, 0x4C, 0x91, 0x67, 0x13, 0xD0, 0x1C, 0x44, 0x76, 0xD6, 0x39, 0xCF, 0xC5, 0xD1, 0xA0, 0xE4,
    0x23, 0xBB, 0xE8, 0xF2, 0xCB, 0x2B, 0x05, 0xBE, 0x0E, 0x86, 0x08, 0x5C, 0x0B, 0x60, 0x21, 0x45,
    0x8C, 0xA2, 0x03, 0x28, 0x0B, 0x67, 0x37, 0xBD, 0xFE, 0xE0, 0x76, 0x48, 0x47, 0xE3, 0xBB, 0x0A,
    0x58, 0x32, 0x49, 0xC3, 0xFB, 0x98, 0x3F, 0x24, 0xE9, 0x24, 0x0B, 0x72, 0x40, 0x0C, 0x63, 0x3E,
    0x4D, 0xD2, 0xD9, 0x63, 0xA0, 0x4A, 0x72, 0x10, 0x89, 0x59, 0x56, 0x95, 0x4D, 0x77, 0x30, 0x7F,
    0x7A, 0x7E, 0xC9, 0x0E, 0xE5, 0x58, 0x05, 0xAF, 0xFC, 0x6D, 0xF1, 0xFE, 0x71, 0x54, 0x53, 0x8B,
    0xC9, 0xB6, 0x9F, 0x5F, 0xFC, 0x7B, 0xF9, 0x53, 0x6F, 0xE4, 0xAB, 0xCB, 0xD1, 0xBF, 0x7F, 0xAB,
    0x75, 0xF3, 0xF8, 0x64, 0x7F, 0x1C, 0xDD, 0x9C, 0xB6, 0xDA, 0x85, 0x22, 0xFC, 0x3F, 0x7F, 0x0B,
    0xBB, 0x57, 0x1D, 0xEF, 0xFB, 0xD7, 0x46, 0xF7, 0x00, 0x00, 0x00, 0x25, 0x74, 0x45, 0x58, 0x74,
    0x64, 0x61, 0x74, 0x65, 0x3A, 0x63, 0x72, 0x65, 0x61, 0x74, 0x65, 0x00, 0x32, 0x30, 0x31, 0x38,
    0x2D, 0x30, 0x39, 0x2D, 0x31, 0x38, 0x54, 0x31, 0x37, 0x3A, 0x30, 0x35, 0x3A, 0x30, 0x30, 0x2B,
    0x30, 0x32, 0x3A, 0x30, 0x30, 0x45, 0x90, 0x54, 0xFF, 0x00, 0x00, 0x00, 0x25, 0x74, 0x45, 0x58,
    0x74, 0x64, 0x61, 0x74, 0x65, 0x3A, 0x6D, 0x6F, 0x64, 0x69, 0x66, 0x79, 0x00, 0x32, 0x30, 0x31,
    0x38, 0x2D, 0x30, 0x39, 0x2D, 0x31, 0x38, 0x54, 0x31, 0x37, 0x3A, 0x30, 0x35, 0x3A, 0x30, 0x30,
    0x2B, 0x30, 0x32, 0x3A, 0x30, 0x30, 0x34, 0xCD, 0xEC, 0x43, 0x00, 0x00, 0x00, 0x57, 0x7A, 0x54,
    0x58, 0x74, 0x52, 0x61, 0x77, 0x20, 0x70, 0x72, 0x6F, 0x66, 0x69, 0x6C, 0x65, 0x20, 0x74, 0x79,
    0x70, 0x65, 0x20, 0x69, 0x70, 0x74, 0x63, 0x00, 0x00, 0x78, 0x9C, 0xE3, 0xF2, 0x0C, 0x08, 0x71,
    0x56, 0x28, 0x28, 0xCA, 0x4F, 0xCB, 0xCC, 0x49, 0xE5, 0x52, 0x00, 0x03, 0x23, 0x0B, 0x2E, 0x63,
    0x0B, 0x13, 0x23, 0x13, 0x4B, 0x93, 0x14, 0x03, 0x13, 0x20, 0x44, 0x80, 0x34, 0xC3, 0x64, 0x03,
    0x23, 0xB3, 0x54, 0x20, 0xCB, 0xD8, 0xD4, 0xC8, 0xC4, 0xCC, 0xC4, 0x1C, 0xC4, 0x07, 0xCB, 0x80,
    0x48, 0xA0, 0x4A, 0x2E, 0x00, 0xEA, 0x17, 0x11, 0x74, 0xF2, 0x42, 0x35, 0x95, 0x00, 0x00, 0x00,
    0x00, 0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82
};

const HTTPSRV_FS_DIR_ENTRY httpsrv_fs_data[] = {
    {"/index.html", 0, (unsigned char *)httpsrv_fs_webpage_my_index_html, sizeof(httpsrv_fs_webpage_my_index_html) - 1},
    {"/style.css", 0, (unsigned char *)httpsrv_fs_webpage_my_style_css, sizeof(httpsrv_fs_webpage_my_style_css) - 1},
    {"/evbConf.js", 0, (unsigned char *)httpsrv_fs_webpage_evb_conf_js, sizeof(httpsrv_fs_webpage_evb_conf_js) - 1},
    {"/favicon-16x16.png", 0, (unsigned char *)httpsrv_fs_webpage_my_favicon, sizeof(httpsrv_fs_webpage_my_favicon)},
    {0, 0, 0, 0}
};

