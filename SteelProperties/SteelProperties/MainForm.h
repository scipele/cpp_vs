#pragma once
#include "ShapeManager.hpp" // Include the ShapeManager header
#include "SteelShapes.hpp"
#include <msclr/marshal_cppstd.h>


namespace SteelProperties {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace msclr::interop;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	// ShapeManager as a member of the MainForm class
	private: ShapeManager^ shapeManager;

	public:
		MainForm(void)
		{
			InitializeComponent();
			shapeManager = gcnew ShapeManager();

			// Add the strings to the comboBox
			comboBox1->Items->AddRange(gcnew cli::array<String^> {
				"W", "M", "S", "HP", "C", "MC", "L", "WT", "MT", "ST", "2L", "HSS", "PIPE"
			});

			// Read shapes from the file
			shapeManager->ReadShapesFromFile("Data/ShapeDescriptions.csv");
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private:
		System::Windows::Forms::Label^ label1;
		System::Windows::Forms::Label^ label2;
		System::Windows::Forms::Label^ label3;
		System::Windows::Forms::ComboBox^ comboBox1;
		System::Windows::Forms::ComboBox^ comboBox2;
		System::Windows::Forms::TextBox^ textBox1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(86, 9);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(129, 21);
			this->comboBox1->TabIndex = 0;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::comboBox1_SelectedIndexChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(68, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Shape Type:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(270, 9);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(79, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Full Description";
			// 
			// comboBox2
			// 
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Location = System::Drawing::Point(376, 6);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(324, 21);
			this->comboBox2->TabIndex = 3;
			this->comboBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::comboBox2_SelectedIndexChanged);
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Courier New", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(86, 41);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(910, 608);
			this->textBox1->TabIndex = 4;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(12, 41);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(57, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Properties:";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1008, 661);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->comboBox1);
			this->Name = L"MainForm";
			this->Text = L"Steel Properties";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: 
		void MainForm::comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
		{
			// Cast the sender object to a ComboBox
			System::Windows::Forms::ComboBox^ comboBox = (System::Windows::Forms::ComboBox^)sender;

			// Get the selected index
			int selectedIndex = comboBox->SelectedIndex;

			// Check if shapeManager is initialized
			if (shapeManager == nullptr) {
				System::Windows::Forms::MessageBox::Show("Error: shapeManager is not initialized.");
				return;
			}

			// Clear ComboBox2 before updating
			comboBox2->Items->Clear();

			// Check if selectedIndex is valid
			if (selectedIndex >= 0 && selectedIndex < shapeManager->shapes->Length) {
				// Get the shapes corresponding to the selected index
				List<Shape^>^ selectedShapes = shapeManager->shapes[selectedIndex];

				// Populate ComboBox2 with shape names
				for each (Shape ^ shape in selectedShapes) {
					comboBox2->Items->Add(shape->name);
				}

				// Optionally select the first item in ComboBox2
				if (comboBox2->Items->Count > 0) {
					comboBox2->SelectedIndex = 0;
				}
			}
		}


	private: System::Void comboBox2_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		System::String^ selectedShape = comboBox2->SelectedItem->ToString();

		// Convert the managed string (System::String^) to a native std::string
		std::string nativeShape = msclr::interop::marshal_as<std::string>(selectedShape);
		
		SteelShapes shape;  // native C++ class
		shape.pass_str_from_user(nativeShape);
		std::string nativeOutput = shape.GetShapeProperties();

		// Convert std::string to System::String
		String^ managedStr = gcnew String(nativeOutput.c_str());

		// Display the string in textBox1 instead of using MessageBox
		textBox1->Text = managedStr;
	}
};
}