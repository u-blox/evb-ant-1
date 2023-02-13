function checkDHCPToggles(){
	let enetDHCP = document.getElementById("enetuseDHCP").checked;
	let wifiDHCP = document.getElementById("wifiuseDHCP").checked;

	document.getElementById("enetip").disabled = enetDHCP;
	document.getElementById("enetmask").disabled = enetDHCP;
	document.getElementById("enetgw").disabled = enetDHCP;
	document.getElementById("enetdns1").disabled = enetDHCP;
	document.getElementById("enetdns2").disabled = enetDHCP;

	document.getElementById("wifiip").disabled = wifiDHCP;
	document.getElementById("wifimask").disabled = wifiDHCP;
	document.getElementById("wifigw").disabled = wifiDHCP;
	document.getElementById("wifidns1").disabled = wifiDHCP;
	document.getElementById("wifidns2").disabled = wifiDHCP;
}

function toggleShowPassword(){
	let input = document.getElementById("passw");
	let icon = document.getElementById("togglePassw");
	if (input.type === "password"){
		input.type = "text";
		icon.className = "far fa-eye-slash";
	} else {
		input.type = "password";
		icon.className = "far fa-eye";
	}
}

function doReboot(){
	const xhttp = new XMLHttpRequest();
	xhttp.open("GET", "reboot.cgi");
	xhttp.send();
}	

function doNinaReset(){
	const xhttp = new XMLHttpRequest();
	xhttp.open("GET", "nina_reset.cgi");
	xhttp.send();
}	

function doNinaSw1(){
	const xhttp = new XMLHttpRequest();
	xhttp.open("GET", "nina_sw1.cgi");
	xhttp.send();
}

function doNinaSw2(){
	const xhttp = new XMLHttpRequest();
	xhttp.open("GET", "nina_sw2.cgi");
	xhttp.send();
}	

function getUptimeData(){
	const xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = parseRTCData;
	xhttp.open("GET", "rtcdata.cgi");
	xhttp.send();
}

function parseRTCData(){
	if (this.readyState === XMLHttpRequest.DONE) {
      	if (this.status === 200) {
      		let response = this.responseText.split("\n");
      		document.getElementById("time").innerHTML = leftPadIfNeeded(response[0]) + ":" + leftPadIfNeeded(response[1]) + ":" + leftPadIfNeeded(response[2]);
      		setTimeout(getUptimeData, 1000);
      	}
  	}
}

function leftPadIfNeeded(input){
	return (input < 10)? '0' + input : input;
}

function getFirmwareVersion(){
	const xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = handleFWVersion;
	xhttp.open("GET", "get_version.cgi");
	xhttp.send();
}

function handleFWVersion(){
	if (this.readyState === XMLHttpRequest.DONE) {
      	if (this.status === 200) {
      		document.getElementById("firmwareVersionLabel").innerHTML += this.responseText;
      	}
  	}	
}

function doSubmitConf() {

	let content = {};
	content.wifien = document.getElementById("wifiEnabled").checked;
	content.ssid = document.getElementById("ssid").value;
	content.password = document.getElementById("passw").value;
	content.enetip = document.getElementById("enetip").value;
	content.enetmask = document.getElementById("enetmask").value;
	content.enetgw = document.getElementById("enetgw").value;
	content.enetdns1 = document.getElementById("enetdns1").value;
	content.enetdns2 = document.getElementById("enetdns2").value;
	content.enetuseDHCP = document.getElementById("enetuseDHCP").checked;
	content.posengip = document.getElementById("posengip").value;
	content.posengport = document.getElementById("posengport").value;
	content.wifiip = document.getElementById("wifiip").value;
	content.wifimask = document.getElementById("wifimask").value;
	content.wifigw = document.getElementById("wifigw").value;
	content.wifidns1 = document.getElementById("wifidns1").value;
	content.wifidns2 = document.getElementById("wifidns2").value;
	content.wifiuseDHCP = document.getElementById("wifiuseDHCP").checked;
	content.eneten = document.getElementById("enetEnabled").checked;
	content.onboardNina = (document.getElementById("activeNINA").value === "onboard");

	const xhttp = new XMLHttpRequest();
	xhttp.open("POST", "post.cgi");
	xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
	xhttp.send("post_input=" + JSON.stringify(content));
}


function doReadConf(){
	const xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = parseConfResponse;
	xhttp.open("GET", "get.cgi");
	xhttp.send();
}

function parseConfResponse() {
    if (this.readyState === XMLHttpRequest.DONE) {
      if (this.status === 200) {
      	let response = JSON.parse(this.responseText);

      	document.getElementById("wifiEnabled").checked = response.wifien;
    	document.getElementById("ssid").value = response.ssid;
		document.getElementById("passw").value = response.password;
		document.getElementById("enetip").value = response.enetip;
		document.getElementById("enetmask").value = response.enetmask;
		document.getElementById("enetgw").value = response.enetgw;
		document.getElementById("enetdns1").value = response.enetdns1;
		document.getElementById("enetdns2").value = response.enetdns2;
		document.getElementById("enetuseDHCP").checked = response.enetuseDHCP;
		document.getElementById("posengip").value = response.posengip;
		document.getElementById("posengport").value = response.posengport;
		document.getElementById("wifiip").value = response.wifiip;
		document.getElementById("wifimask").value = response.wifimask;
		document.getElementById("wifigw").value = response.wifigw;
		document.getElementById("wifidns1").value = response.wifidns1;
		document.getElementById("wifidns2").value = response.wifidns2;
		document.getElementById("wifiuseDHCP").checked = response.wifiuseDHCP;
		document.getElementById("enetEnabled").checked = response.eneten;
		document.getElementById("activeNINA").value = (response.onboardNina) ? "onboard" : "antb10";
		document.getElementById("wifirssi").innerText = (response.wifirssi > -256) ? response.wifirssi : " - ";

		checkDHCPToggles();

      } else {
        alert('There was a problem with the request.');
      }
    }
}

function doAtSend() {
	const xhttp = new XMLHttpRequest();
	xhttp.open("POST", "at_cmd.cgi");
	xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
	xhttp.send("command=" + document.getElementById("atcommand").value + "\r");
	console.log("Sent", document.getElementById("atcommand").value + "\r")
}

function windowOnLoad() {
  	getUptimeData();
  	doReadConf();
	getFirmwareVersion();
}

window.onload = windowOnLoad;
