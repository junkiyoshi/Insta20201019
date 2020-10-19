#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(90);

	int hue = ofGetFrameNum() % 255;
	ofColor color;

	int span = 15;
	ofMesh face, frame;
	frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
	float frame_step = 0.04;
	float len_step = 0.002;

	auto noise_param = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
	for (float len = ofGetWidth(); len > 0; len -= span) {

		int index = face.getNumVertices();

		auto loc = glm::vec3(
			len * ofMap(ofNoise(noise_param.x, ofGetFrameNum() * frame_step + len * len_step), 0, 1, 0, 0.3),
			len * ofMap(ofNoise(noise_param.y, ofGetFrameNum() * frame_step + len * len_step), 0, 1, 0, 0.3),
			len * ofMap(ofNoise(noise_param.z, ofGetFrameNum() * frame_step + len * len_step), 0, 1, 0, 0.3)
		);

		auto next = glm::vec3(
			(len - span) * ofMap(ofNoise(noise_param.x, ofGetFrameNum() * frame_step + (len - span) * len_step), 0, 1, 0, 0.3),
			(len - span) * ofMap(ofNoise(noise_param.y, ofGetFrameNum() * frame_step + (len - span) * len_step), 0, 1, 0, 0.3),
			(len - span) * ofMap(ofNoise(noise_param.z, ofGetFrameNum() * frame_step + (len - span) * len_step), 0, 1, 0, 0.3)
		);

		face.addVertex(glm::vec3(loc.x, loc.y, loc.z));
		face.addVertex(glm::vec3(-loc.x, loc.y, loc.z));
		face.addVertex(glm::vec3(-next.x, next.y, next.z));
		face.addVertex(glm::vec3(next.x, next.y, next.z));

		color.setHsb((int)(hue + len / 6) % 255, 255, 180);
		face.addColor(color);
		face.addColor(color);
		face.addColor(color);
		face.addColor(color);

		frame.addVertex(glm::vec3(loc.x, loc.y, loc.z));
		frame.addVertex(glm::vec3(-loc.x, loc.y, loc.z));
		frame.addVertex(glm::vec3(-next.x, next.y, next.z));
		frame.addVertex(glm::vec3(next.x, next.y, next.z));

		face.addIndex(index + 0); face.addIndex(index + 1); face.addIndex(index + 2);
		face.addIndex(index + 0); face.addIndex(index + 2); face.addIndex(index + 3);

		frame.addIndex(index + 0); frame.addIndex(index + 3);
		frame.addIndex(index + 1); frame.addIndex(index + 2);
	}

	frame.addIndex(0); frame.addIndex(1);
	frame.addIndex(frame.getNumVertices() - 1); frame.addIndex(frame.getNumVertices() - 2);


	for (int i = 0; i < 8; i++) {

		ofRotateX(45);

		ofSetColor(39);
		face.draw();

		ofSetColor(239);
		frame.drawWireframe();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}