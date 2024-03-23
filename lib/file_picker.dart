import "package:flutter/material.dart";
import 'dart:io';
import 'package:file_picker/file_picker.dart';

class File_picker extends StatelessWidget {
  const File_picker({super.key});

  Future<void> _pickFile() async {
    FilePickerResult? result = await FilePicker.platform.pickFiles();

    if (result != null) {
      PlatformFile file = result.files.first;

      try {
        await saveFile(file.path!, file.name);
      } catch (e) {
        print('Error saving file: $e');
      }
    } else {
      // User canceled the picker
      print('User canceled the file picking');
    }
  }

  Future<void> saveFile(String filePath, String name) async {
    final File pickedFile = File(filePath);
    final username = name;
    String currentDirectory = Directory.current.path;
    final String savePath = '$currentDirectory/lib/$username';

    // Copy the file to the desired location
    await pickedFile.copy(savePath);
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Center(
        child: ElevatedButton(
          onPressed: _pickFile,
          child: Text('Pick a File'),
        ),
      ),
    );
  }
}
