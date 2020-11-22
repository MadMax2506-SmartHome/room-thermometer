# ESP - Room Thermometer

## Allgemein
* Gerätename: `room_thermometer`


## Setup

### ESP32 einbinden
<ol>
	<li>Arduino IDE  öffnen</li>
	<li>Voreinstellungen öffnen: Datei > Voreinstellungen</li>
	<li>
		folgende Links zu Zusätzliche Boardverwalter URLs hinzufügen:
        <ul>
	        <li>https://dl.espressif.com/dl/package_esp32_index.json</li>
			<li>https://arduino.esp8266.com/stable/package_esp8266com_index.json</li>
		</ul>
     </li>
    <li>Voreinstellungen schließen</li>
    <li>Boardverwalter  öffnen: Werkzeuge > Board > Boardverwalter</li>
    <li>Boards von <b>esp8266 (by ESP8266 Community)</b> installieren -> <b>zu suchen: "esp8266"</b></li>
    <li>Boardverwalter schließen </li>
    <li>Board auswählen: Werkzeuge > Board > <b>LOLIN (Wemos) D1 R2 & mini </b></li>
</ol>

### Bibliotheken einbinden
<ol>
	<li>Arduino IDE  öffnen</li>
    <li>Bibliothekverwalter  öffnen: Werkzeuge > Bibliothek verwalten  </li>
    <li>
	    folgende Bibliotheken installieren:
        <ul>
	        <li>ArduinoOTA (by Arduino, Juraj Andrassy) -> <b>zu suchen: "ota"</b></li>
	        <li>SimpleDHT (by Winlin) -> <b>zu suchen: "simple dht"</b></li>
	        <li>PubSublient (by Nick O'Leary) -> <b>zu suchen: "pubsub client"</b></li>
		    </ul>
    </li>
</ol>

### Refresh over the air
<ol>
	<li>Arduino IDE öffnen</li>
    <li>Netzwerkschnittstelle auswählen: Werkzeuge > Port > <i>*Mac-Adresse*</i></li>
    <li>Code hochladen</li>
</ol>
