import 'package:flutter/material.dart';
import 'Pages/data_grid.dart';
import 'Pages/file_picker.dart';

class HomePage1 extends StatefulWidget {
  @override
  _HomePageState createState() => _HomePageState();
}

class _HomePageState extends State<HomePage1> {
  int _selectedIndex = 0;

  void _onItemTapped(int index) {
    setState(() {
      _selectedIndex = index;
    });
  }

  @override
  Widget build(BuildContext context) {
    late Widget content;
    switch (_selectedIndex) {
      case 0:
        content = MyHomePage(choice: _selectedIndex);
        break;
      case 1:
        content = File_picker();
        break;
      case 2:
        content = MyHomePage(choice: _selectedIndex);
        break;
      case 3:
        content = MyHomePage(choice: _selectedIndex);
    }

    return Scaffold(
      appBar: AppBar(
        centerTitle: false,
        backgroundColor: const Color.fromARGB(255, 105, 238, 240),
        title: const Text('Invento', style: TextStyle(color: Colors.black)),
        toolbarHeight: 40,
      ),
      body: Row(
        children: <Widget>[
          NavigationRail(
            selectedIndex: _selectedIndex,
            onDestinationSelected: _onItemTapped,
            labelType: NavigationRailLabelType.all,
            destinations: const [
              NavigationRailDestination(
                icon: Icon(Icons.home),
                label: Text('Home'),
              ),
              NavigationRailDestination(
                icon: Icon(Icons.shopping_cart),
                label: Text('Add Products'),
              ),
              NavigationRailDestination(
                icon: Icon(Icons.production_quantity_limits),
                label: Text('Low Stock'),
              ),
              NavigationRailDestination(
                icon: Icon(Icons.sell),
                label: Text('Sales'),
              ),
            ],
          ),
          const VerticalDivider(thickness: 1, width: 1),
          Expanded(
            child: Container(
              padding: const EdgeInsets.all(20),
              child: content,
            ),
          ),
        ],
      ),
    );
  }
}
