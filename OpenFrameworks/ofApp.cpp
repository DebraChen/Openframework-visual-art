#include "ofApp.h"

void ofApp::setup(){
    ofBackground(255);
    ofSetFrameRate( 60 );
    cam.setPosition( 0, 0, 20 );
    cam.lookAt( ofVec3f(0,0,0));
    cam.enableStereo();
    cam.setNearClip(1);
    setupRandomBoxes();
    setupGrid();
}

//--------------------------------------------------------------
void ofApp::setupRandomBoxes()
{
    for( int i = 0; i < 100; i++ ) {
        ofBoxPrimitive box;
        box.set( ofRandom(0.3, 0.6) );
        //box.rollDeg( ofRandom(0, 180));
        box.tiltDeg( ofRandom(0, 180));
        float tx = ofRandom( -5, 5 );
        float ty = ofRandom( -3, 3 );
        float tz = ofRandom( -5, 5 );
        box.setPosition( tx, ty, tz );
        boxes.push_back(box);
        colors.push_back( ofColor( ofRandom(40,55), ofRandom(100, 160), ofRandom(130, 220)));
    }
}
//--------------------------------------------------------------
void  ofApp::setupGrid(){
    for(int x=-5;x<=5;x+=2){
        for(int y=-5;y<=5;y+=2){
            for(int z=-5;z<=5;z+=2){
                ofBoxPrimitive box;
                box.set(0.5);
                box.setPosition(x,y,z);
                nodes.push_back(box);
            }
        }
    }
    for(int i=0;i<nodes.size();i++){
        for(int j=0;j<nodes.size();j++){
            ofVec3f iNode=nodes[i].getPosition();
        ofVec3f jNode= nodes[j].getPosition();
            float distance=ofDist(iNode.x,iNode.y,iNode.z,jNode.x,jNode.y,jNode.z);
            if(distance == 2){
                startLine.push_back(iNode);
                endLine.push_back(jNode);
        }
        }
    }
}
//--------------------------------------------------------------
void  ofApp::drawGrid(){
    ofPushMatrix();
    float sine=sin(ofDegToRad(ofGetFrameNum()));
    ofTranslate(0,0, sine*10);
    ofRotateDeg(sine*PI*50, 0,5.f,1) ;
    for(int i=0;i<nodes.size();i++){
       // ofDrawGrid(10,10,true,false,true,false);
     //   ofDrawGrid();
        nodes[i].draw();
    }
        for(int j=0;j<startLine.size();j++){
          ofDrawLine( startLine[j],endLine[j]);
        }
    ofPopMatrix();
}
//--------------------------------------------------------------
void ofApp::update(){
    cam.eyeSeparation   = ofMap( ofGetMouseX(), 0, ofGetWidth(), 0, 1., true );
    cam.focalLength     = ofMap( ofGetMouseY(), 0, ofGetHeight(), 0, 100, true );
    
  //  cam.orbitDeg( ofGetElapsedTimef() * 3.f, 0.2f, 15 );
}

//-----------------------------------------------------------------------
void ofApp::draw() {
    
    
    ofEnableDepthTest();
    ofLight light;
    light.enable();
    
  
    if( cam.isStereo() ) {
        cam.beginLeft();
    } else {
        cam.begin();
    }
 
   // drawRandomBoxes();
    drawGrid();
    
    // draw again into the right eye
    if( cam.isStereo() ) {
        cam.beginRight();
       // drawRandomBoxes();
        drawGrid();
    }

    if( cam.isStereo() ) {
        cam.endStereo();
    } else {
        cam.end();
    }
    

    light.disable();
    ofDisableDepthTest();
    
    ofSetColor(30, 30, 30 );
    ofDrawBitmapString("Eye Separation: "+ofToString( cam.eyeSeparation, 3), 40, 40 );
    ofDrawBitmapString("Eye Focal Length: "+ofToString( cam.focalLength, 3), 40, 60 );
}

//--------------------------------------------------------------
void ofApp::drawRandomBoxes()
{
    for( int i = 0; i < boxes.size(); i++ ) {
        ofSetColor( colors[i] );
        boxes[i].draw();
        ofSetColor(30, 30, 30);
        ofDrawLine( ofPoint(0,0,0), boxes[i].getPosition() );
    }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == ' ' ) {
        if( cam.isStereo() ){
            cam.disableStereo();
        }else{
            cam.enableStereo();
        }
    }
    if( key == 'f' ) {
        ofToggleFullscreen();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
