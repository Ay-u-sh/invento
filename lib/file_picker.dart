
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
        await saveFile(file.path!);
      } catch (e) {
        print('Error saving file: $e');
      }
    } else {
      print('User canceled the file picking');
    }
  }

  Future<void> saveFile(String filePath) async {
    final File pickedFile = File(filePath);
    final name= "example.csv";
    final String savePath = './INVENTO/lib/$name';
    await pickedFile.copy(savePath);
  }
  
  @override
  Widget build(BuildContext context) {
    return  Scaffold(
        body: 
       Center(
        child:ElevatedButton(
          onPressed: _pickFile,
          child: Text('Pick a File'),
        ),
       ),
      );
    }
  }