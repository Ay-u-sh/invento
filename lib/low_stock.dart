import 'dart:ffi';
import 'hel.dart';
import 'file_parsing.dart';

List<userData> lowStock(int limit) {
  Pointer<DatabaseHandler> dbhandler =
      getSqliteConnection("lib/example.db", "product");
  List<userData> productList = [];
  String data = getLowStockDataSqlite(dbhandler, limit, '|');
  while (data != '|') {
    productList.add(userData(data));
    data = getLowStockDataSqlite(dbhandler, limit, '|');
  }
  closeSqliteConnection(dbhandler);
  return productList;
}
