import 'package:flutter/material.dart';
import 'home_page.dart';
import 'dart:ffi';
// By Ayush Bhande, Ayush Bhardwaj, Devesh Phulara, Divesh Mittal
void main() {
  DynamicLibrary.open('lib/BACKEND/DLL/sqlite3.dll');
  DynamicLibrary.open('lib/BACKEND/DLL/libdesign.dll');
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: HomePage1(),
      themeMode: ThemeMode.light,
      theme: ThemeData(primarySwatch: Colors.teal),
      darkTheme: ThemeData(
        brightness: Brightness.dark,
      ),
      debugShowCheckedModeBanner: false,
    );
  }
}
