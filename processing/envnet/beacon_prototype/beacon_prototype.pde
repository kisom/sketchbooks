import android.content.Intent;
import android.os.Bundle;

import ketai.camera.*;
import ketai.cv.facedetector.*;
import ketai.data.*;
import ketai.net.*;
import ketai.net.bluetooth.*;
import ketai.net.nfc.*;
import ketai.net.nfc.record.*;
import ketai.net.wifidirect.*;
import ketai.sensors.*;
import ketai.ui.*;

KetaiBluetooth ble;

//********************************************************************
// The following code is required to enable bluetooth at startup.
//********************************************************************
void onCreate(Bundle savedInstanceState) {
  super.onCreate(savedInstanceState);
  ble = new KetaiBluetooth(this);
}

void onActivityResult(int requestCode, int resultCode, Intent data) {
  ble.onActivityResult(requestCode, resultCode, data);
}

//********************************************************************

void setup() {
	println("starting bluetooth listener");
	ble.start();
	ble.discoverDevices();
}

void draw() {
	ArrayList<String> names;
	println("discovered devices:");
	names = ble.getDiscoveredDeviceNames();
	for (int i = 0; i < names.size(); i++) {
		println(names.get(i));
	}
}
