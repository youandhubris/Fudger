#include "ofApp.h"
#include "IconsFontAwesome5.h"

static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 }; // Will not be copied by AddFont* so keep in scope.

															 //--------------------------------------------------------------
void ofApp::setup()
{
	/*   SETTINGS   */
	// ofSetLogLevel(OF_LOG_);
	ofSetDataPathRoot("../../_SharedData/");

	settings.setup();
	//settings.load("fudgerSettings.json");


	ofDisableArbTex();
	ofSetBackgroundAuto(false);
	ofSetVerticalSync(true);

	string t = (string) settings.general.getString("Title") + " " + (string)settings.general.getString("Version");
	ofSetWindowTitle(t);	

	/*   GUI   */

	for (int i = 0; i < 5; i++)
	{
		baseLayer b = baseLayer(i);
		layers.push_back(b);
	}
	
	ImGuiIO &io = ImGui::GetIO();
	io.Fonts->AddFontDefault();


	
	ImFontConfig config;
	config.MergeMode = false;
	config.PixelSnapH = true;


	//const char robotoFile[] = "D:\\Hubris\\openFrameworks\\Projects\\_SharedData\\Hack-Regular.ttf";
	//robotoFont = io.Fonts->AddFontFromFileTTF(robotoFile, 32, &config);

	config.MergeMode = false;

#ifdef TARGET_OSX
	const char awesomeFile[] = "/";
#else
	const char awesomeFile[] = "D:\\Hubris\\openFrameworks\\Projects\\_SharedData\\fa-solid-900.ttf";
#endif
	
	awesomeFont = io.Fonts->AddFontFromFileTTF(awesomeFile, 13, &config, icons_ranges);
	//io.Fonts->Build();

	gui.setup();

	//io.Fonts->Build();



}

//--------------------------------------------------------------
void ofApp::update()
{
	// ImGui::GetIO().FontGlobalScale = mouseX / (float) ofGetWidth() * 10.f;
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(ofColor::grey);
	gui.begin();

	//ofDrawBitmapString(windowOpen, 20, 20);

	// bool windowOpen = settings.params.getGroup("Menu Bar").getBool("Window Open");
	// Main body of the Demo window starts here.
	// Early out if the window is collapsed, as an optimization.
	
	// settings.menuBar.getVec2f("Window Size").set(glm::vec2(ofGetWidth(), mouseY));

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			
			if (ImGui::MenuItem("Undo", "CTRL+Z")) { cout << "Log" << "\n"; }
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View"))
		{
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Window"))
		{
			if (ImGui::MenuItem("Layers", "Ctrl+N", &settings.layersWindowOpen)) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}


	if (settings.layersWindowOpen)
	{
		ImGui::Begin("Layers", &settings.layersWindowOpen, settings.layersWindow.getInt("Window Flags"));
		ImGui::Indent();

		enum Mode
		{
			Mode_Insert,
			Mode_Copy,
			Mode_Swap
		};
		static int mode = 0;
		
		
		for (int index = 0; index < layers.size(); index++)
		{
			ImGui::PushID(index);
				
			ImGui::Button(to_string(index).c_str(), glm::vec2(50, 0));

			// Our buttons are both drag sources and drag targets here!
			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
			{
				ImGui::SetDragDropPayload("DND_DEMO_CELL", &index, sizeof(int));        // Set payload to carry the index of our item (could be anything)
				if (mode == Mode_Insert) { ImGui::Text("Insert %s", layers[index].name); }        // Display preview (could be anything, e.g. when dragging an image we could decide to display the filename and a small preview of the image, etc.)
				if (mode == Mode_Copy) { ImGui::Text("Copy %s", layers[index].name); }
				if (mode == Mode_Swap) { ImGui::Text("Swap %s", layers[index].name); }
				ImGui::EndDragDropSource();
			}
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
				{
					IM_ASSERT(payload->DataSize == sizeof(int));
					int newIndex = *(const int*)payload->Data;

					if (mode == Mode_Insert)
					{
						layers.insert(layers.begin() + index, layers[newIndex]);
						int indexToErase = newIndex > index ? newIndex + 1 : newIndex;
						layers.erase(layers.begin() + indexToErase);
					}
					if (mode == Mode_Copy)
					{
						layers[index] = layers[newIndex];
					}
					if (mode == Mode_Swap)
					{
						baseLayer tmp = layers[index];
						layers[index] = layers[newIndex];
						layers[newIndex] = tmp;
					}
				}
				ImGui::EndDragDropTarget();
			}

			ImGui::SameLine();
			ImGui::PushItemWidth(150);
			ImGui::InputText("", &layers[index].name[0], layers[index].name.size() + 1);
			Spacing(glm::vec2(20, 0), true);

			ImGui::SameLine();
			ImGui::Checkbox("Hide", &layers[index].isHidden);
			Spacing(glm::vec2(20, 0), true);

			ImGui::SameLine();
			ImGui::Checkbox("Lock", &layers[index].isLocked);

			ImGui::PopID();
		}
			

		Spacing(glm::vec2(0, 10));



		ImGui::Separator();
		if (ImGui::RadioButton("Insert", mode == Mode_Insert)) { mode = Mode_Insert; } ImGui::SameLine();
		if (ImGui::RadioButton("Copy", mode == Mode_Copy)) { mode = Mode_Copy; } ImGui::SameLine();
		if (ImGui::RadioButton("Swap", mode == Mode_Swap)) { mode = Mode_Swap; }

		Spacing(glm::vec2(10, 0), true);
		ImGui::SameLine();
		ShowHelpMarker("Drag and drop to insert/copy/swap layers");

		ImGui::PushFont(awesomeFont);
		ImGui::SameLine();
		ImGui::Text(ICON_FA_ADJUST);
		ImGui::SameLine();
		ImGui::Text(ICON_FA_ADDRESS_CARD);
		ImGui::SameLine();
		ImGui::Text(ICON_FA_PLUS_SQUARE);
		ImGui::SameLine();
		ImGui::Text(ICON_FA_SQUARE_FULL);
		ImGui::SameLine();
		ImGui::Text(ICON_FA_PLUS);
		ImGui::PopFont();


		ImGui::Button(ICON_FA_COPY, glm::vec2(25, 25));





		ImGui::Unindent();
		ImGui::End();
	}

	
	gui.end();

	for (int i = 0; i < layers.size(); i++)
	{
		ofDrawBitmapStringHighlight(layers[i].name, 50, 50 + i * 20);
		ofDrawBitmapStringHighlight(to_string(layers[i].isHidden), 150, 50 + i * 20);
		ofDrawBitmapStringHighlight(to_string(layers[i].isLocked), 170, 50 + i * 20);
	}

}

void ofApp::Spacing(glm::vec2 v, bool sameLine)
{
	if (sameLine) ImGui::SameLine();
	ImGui::ItemSize(v);
}

// Helper to display a little (?) mark which shows a tooltip when hovered.
void ofApp::ShowHelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
