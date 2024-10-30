#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(315);

	int v_span = 8;
	int u_span = 2;
	int R = 200;

	ofMesh face, line;
	line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	int r = 70;
	float noise_seed = ofRandom(1000);

	for (int i = 0; i < 6; i++) {

		for (int v = 0; v <= 360; v += v_span * 1.5) {

			int u_start = i * 60 + ofMap(ofNoise(noise_seed, cos(v * DEG_TO_RAD) * 0.15, sin(v * DEG_TO_RAD) * 0.15, ofGetFrameNum() * 0.0025), 0, 1, -720, 720);
			int next_u = i * 60 + ofMap(ofNoise(noise_seed, cos((v + v_span * 0.25) * DEG_TO_RAD) * 0.15, sin((v + v_span * 0.25) * DEG_TO_RAD) * 0.15, ofGetFrameNum() * 0.0025), 0, 1, -720, 720);
			for (int u = u_start; u < u_start + 50; u += u_span) {

				face.addVertex(this->make_point(R, r, u, v));
				face.addVertex(this->make_point(R, r, u + u_span, v));
				face.addVertex(this->make_point(R, r, next_u + u_span, v + v_span * 0.25));
				face.addVertex(this->make_point(R, r, next_u, v + v_span * 0.25));

				line.addVertex(this->make_point(R, r, u, v));
				line.addVertex(this->make_point(R, r, u + u_span, v));
				line.addVertex(this->make_point(R, r, next_u + u_span, v + v_span * 0.25));
				line.addVertex(this->make_point(R, r, next_u, v + v_span * 0.25));

				ofColor face_color = ofColor(0);
				ofColor line_color;
				line_color.setHsb(ofMap(i, 0, 8, 0, 255), 255, 255);

				face.addColor(face_color);
				face.addColor(face_color);
				face.addColor(face_color);
				face.addColor(face_color);

				line.addColor(line_color);
				line.addColor(line_color);
				line.addColor(line_color);
				line.addColor(line_color);

				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 3);
				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 3); face.addIndex(face.getNumVertices() - 4);

				line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 2);
				line.addIndex(line.getNumVertices() - 3); line.addIndex(line.getNumVertices() - 4);

				if (u == u_start) {

					line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 4);
				}

				next_u += u_span;
			}

			line.addIndex(line.getNumVertices() - 2); line.addIndex(line.getNumVertices() - 3);
		}
	}

	face.drawFaces();
	line.drawWireframe();

	this->cam.end();

	/*
	int start = 250;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// ���w�f�b�T������ �`���Ċy���ސ��w�����@P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}