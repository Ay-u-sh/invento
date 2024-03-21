import 'package:flutter/material.dart';
import 'package:syncfusion_flutter_datagrid/datagrid.dart';
import 'package:syncfusion_flutter_core/theme.dart';
import 'file_parsing.dart';
import 'top_selling.dart';
import 'low_stock.dart';

class MyHomePage extends StatefulWidget {

  final int choice;

  const MyHomePage({Key? key, required this.choice}) : super(key: key);

  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  List<userData> products = <userData>[];
  late ProductDataSource productDataSource;

  @override
  void initState() {
    super.initState();
    _updateProductData(widget.choice);
  }

  @override
  void didUpdateWidget(MyHomePage oldWidget) {
    super.didUpdateWidget(oldWidget);
    if (oldWidget.choice != widget.choice) {
      _updateProductData(widget.choice);
    }
  }

  void _updateProductData(int choice) {
    switch (choice) {
      case 0:
        products = getProductData();
        break;
      case 1:
        // Handle other choices here
        break;
      case 2:
        products = lowStock(10);
        break;
      case 3:
        products = topSelling();
        break;
    }
    productDataSource = ProductDataSource(ProductData: products);
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Center(child: const Text('Product Data')),
      ),
      body: SfDataGridTheme(
        data: SfDataGridThemeData(
            rowHoverColor: Color.fromARGB(255, 0, 134, 152),
            rowHoverTextStyle: TextStyle(
              color: Colors.white,
              fontSize: 14,
            ),
            headerColor: Color.fromARGB(255, 0, 142, 152)),
        child: SfDataGrid(
            source: productDataSource,
            columnWidthMode: ColumnWidthMode.fill,
            columns: <GridColumn>[
              GridColumn(
                  columnName: 'ID',
                  label: Container(
                      padding: EdgeInsets.all(16.0),
                      alignment: Alignment.center,
                      child: Text(
                        'ID',
                        style: TextStyle(color: Colors.white),
                      ))),
              GridColumn(
                  columnName: 'PRODUCTNAME',
                  label: Container(
                      padding: EdgeInsets.all(8.0),
                      alignment: Alignment.center,
                      child: Text(
                        'PRODUCT NAME',
                        style: TextStyle(color: Colors.white),
                      ))),
              GridColumn(
                  columnName: 'PRICE',
                  label: Container(
                      padding: EdgeInsets.all(8.0),
                      alignment: Alignment.center,
                      child: Text(
                        'PRICE',
                        overflow: TextOverflow.ellipsis,
                        style: TextStyle(color: Colors.white),
                      ))),
              GridColumn(
                  columnName: 'BRAND',
                  label: Container(
                      padding: EdgeInsets.all(8.0),
                      alignment: Alignment.center,
                      child: Text(
                        'BRAND',
                        style: TextStyle(color: Colors.white),
                      ))),
              GridColumn(
                  columnName: 'QUANTITY',
                  label: Container(
                      padding: EdgeInsets.all(8.0),
                      alignment: Alignment.center,
                      child: Text(
                        'QUANTITY',
                        style: TextStyle(color: Colors.white),
                      ))),
            ],
            gridLinesVisibility: GridLinesVisibility.both,
            headerGridLinesVisibility: GridLinesVisibility.both),
      ),
    );
  }
}

class ProductDataSource extends DataGridSource {
  /// Creates the employee data source class with required details.
  ProductDataSource({required List<userData> ProductData}) {
    _ProductData = ProductData.map<DataGridRow>((e) => DataGridRow(cells: [
          DataGridCell<String>(columnName: 'id', value: e.ID),
          DataGridCell<String>(columnName: 'PRODUCTNAME', value: e.PRODUCTNAME),
          DataGridCell<String>(columnName: 'PRICE', value: e.PRICE),
          DataGridCell<String>(columnName: 'BRAND', value: e.BRAND),
          DataGridCell<String>(columnName: 'QUANTITY', value: e.QUANTITY),
        ])).toList();
  }

  List<DataGridRow> _ProductData = [];

  @override
  List<DataGridRow> get rows => _ProductData;

  @override
  DataGridRowAdapter buildRow(DataGridRow row) {
    return DataGridRowAdapter(
        cells: row.getCells().map<Widget>((e) {
      return Container(
        alignment: Alignment.center,
        padding: EdgeInsets.all(8.0),
        child: Text(e.value.toString()),
      );
    }).toList());
  }
}
