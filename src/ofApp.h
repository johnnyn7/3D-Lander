#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include  "ofxAssimpModelLoader.h"
#include "Octree.h"
#include "Emitter.h"
#include "Shape.h"

inline float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

class Agent : public Particle {
public:
	Agent() : Particle() {}
};

class AgentEmitter : public Emitter {
public:
    void spawnSprite(){
        Agent particle;
		particle.velocity = velocity;
		particle.lifespan = lifespan;
		particle.pos = pos;
		particle.birthtime = ofGetElapsedTimeMillis();
		sys->add(particle);
	}
    
	void moveSprite(Particle* particle) {
		Emitter::moveParticle(particle);
        glm::vec3 v = glm::normalize(particle->velocity);
		glm::vec3 u = glm::vec3(0, -1, 0);
		float a = glm::orientedAngle(u, v, glm::vec3(0, 0, 1));
		particle->rot = glm::degrees(a);
	}
};

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void dragEvent2(ofDragInfo dragInfo);
		void dragEvent(ofDragInfo dragInfo);
		void drawAxis(ofVec3f);
		void initLightingAndMaterials();
		void savePicture();
		void toggleWireframeMode();
		void toggleSelectTerrain();
		void setCameraTarget();
		bool mouseIntersectPlane(ofVec3f planePoint, ofVec3f planeNorm, ofVec3f &point);
		bool raySelectWithOctree(ofVec3f &pointRet);
		glm::vec3 getMousePointOnPlane(glm::vec3 p , glm::vec3 n);
        void drawStarfield();
        void restartGame();
        
        enum CamMode { FREE_CAM, TRACK_CAM, BOTTOM_CAM, TOP_CAM };
        CamMode currentCam = FREE_CAM;
        CamMode lastFixedCam = TRACK_CAM;

		ofEasyCam cam;
		ofxAssimpModelLoader mars, lander;
        Box boundingBox, landerBounds;
		Box testBox;
		vector<Box> colBoxList;
        Octree octree;
		TreeNode selectedNode;
		glm::vec3 mouseDownPos, mouseLastPos;
        glm::vec3 collisionDirection = glm::vec3(0, 0, 0);
        glm::vec3 explosionVelocity;
		        
        ofxPanel gui;
        ofxLabel altitudeLabel;
        ofxLabel fuelLabel;
        ofVec3f selectedPoint;
        ofVec3f intersectPoint;
        ofLight keyLight;
        ofLight fillLight;
        ofLight backLight;
        ofLight shipLight;
    
        bool gameOver = false;
        bool showGameOverText = false;
        bool bLanderSelected = false;
        bool bInDrag = false;
		bool bWireframe;
		bool pointSelected = false;
		bool bDisplayLeafNodes = false;
		bool bDisplayOctree = false;
		bool bDisplayBBoxes = false;
		bool bLanderLoaded;
		bool bTerrainSelected;
        bool bShowTelemetry = false;
        bool explosionActive = false;
        bool bResolveCollision = false;
        bool landingStarted = false;
        bool gameWin = false;
        bool bShipLightOn = false;

		Emitter* shooter = NULL;
		
		const float selectionRange = 4.0;
		float collisionSpeed = 0.1;
		float shipVelocity = 0.0;
		float shipAcceleration = 0.0;
		float shipVelocityX = 0.0;
		float shipAccelerationX = 0.0;
		float shipVelocityZ = 0.0;
		float shipAccelerationZ = 0.0;
        float fuel = 120.0f;
        float fuelTimer = 0.0f;
        float landerRotation = 0.0f;
        float rotationSpeed = 1.0f;
        float landingZoneSize = 15.0f;
    
        vector<Box> bboxList;
        vector<ofPoint> stars;
        vector<glm::vec3> landingZones;

		map<int, bool> keymap;

		ofSoundPlayer   bumpS;
		ofSoundPlayer   crashS;
		ofSoundPlayer   shootS;
		ofSoundPlayer   thrustS;
};
