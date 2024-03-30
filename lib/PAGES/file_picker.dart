import "package:flutter/material.dart";
import 'dart:io';
import 'package:file_picker/file_picker.dart';
import '../LINKER/connect.dart';

String changeSlashes(String str) {
  String x = "";
  for (int i = 0; i < str.length; i++) {
    if (str[i] == '\\')
      x += '/';
    else
      x += str[i];
  }
  return x;
}

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
    final filename = name;
    
    String currentDirectory = Directory.current.path;
    String modifiedDirectory = changeSlashes(currentDirectory);
    
    final String file = '$modifiedDirectory/lib/FILE_UPLOAD/$filename';
    final String database = '$modifiedDirectory/lib/DATABASE/example.db';
    
    await pickedFile.copy(file);
    insertCSVSqlite(file, database, "product");
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
