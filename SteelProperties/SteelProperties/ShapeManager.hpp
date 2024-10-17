#pragma once
// ShapeManager.h
#include <fstream>
#include <sstream>
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace System::Collections::Generic;

public ref class Shape {
public:
    String^ name;

    Shape(String^ n) : name(n) {}
};

public ref class ShapeManager {
public:
    // Declare an array of List<Shape^>^ with 13 elements
    array<List<Shape^>^>^ shapes = gcnew array<List<Shape^>^>(13);

    ShapeManager() {
        for (int i = 0; i < 13; ++i) {
            shapes[i] = gcnew List<Shape^>(); // Initialize each list
        }
    }

    void ReadShapesFromFile(String^ filename) {
        std::ifstream file(msclr::interop::marshal_as<std::string>(filename)); // Convert managed string to std::string

        if (!file.is_open()) {
            // If the file does not open, show an error message
            System::Windows::Forms::MessageBox::Show("Error: Could not open file: " + filename);
            return; // Exit the function
        }

        std::string line;
        int currentTypeIndex = -1;

        while (std::getline(file, line)) {
            if (line.find("NextType:") != std::string::npos) {
                // Move to the next type; increment index
                ++currentTypeIndex;

                // Ensure that the current index is within the bounds
                if (currentTypeIndex < 0 || currentTypeIndex >= 13) {
                    System::Windows::Forms::MessageBox::Show("Error: Invalid type index: " + currentTypeIndex.ToString());
                    break;
                }
            }
            else {
                // If we are still within the range of types, add the shape
                if (currentTypeIndex >= 0 && currentTypeIndex < 13) {
                    // Additional check for nullptr, though it shouldn't be null
                    if (shapes[currentTypeIndex] != nullptr) {
                        shapes[currentTypeIndex]->Add(gcnew Shape(msclr::interop::marshal_as<String^>(line))); // Convert std::string to managed String^
                    }
                }
            }
        }
    }
};