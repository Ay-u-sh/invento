import 'dart:ffi';
import 'package:invento/FRONTEND/file_parsing.dart';
import '../LINKER/connect.dart';

List<userData> topSelling() {
  Pointer<DatabaseHandler> dbhandler =
      getSqliteConnection("lib/./DATABASE/example.db", "product");
  List<userData> productList= [];
  String data = getTopSellingDataSqlite(dbhandler, '|');
  while (data != '|') {
    productList.add(userData(data));
    data = getTopSellingDataSqlite(dbhandler, '|');
  }
  closeSqliteConnection(dbhandler);
  return productList;
}

