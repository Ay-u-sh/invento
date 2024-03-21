import 'dart:ffi';
import 'package:invento/file_parsing.dart';
import 'hel.dart';
List<userData> topSelling() {
  Pointer<DatabaseHandler> dbhandler =
      getSqliteConnection("lib/example.db", "product");
  List<userData> productList= [];
  String data = getTopSellingDataSqlite(dbhandler, '|');
  while (data != '|') {
    productList.add(userData(data));
    data = getTopSellingDataSqlite(dbhandler, '|');
  }
  closeSqliteConnection(dbhandler);
  return productList;
}

