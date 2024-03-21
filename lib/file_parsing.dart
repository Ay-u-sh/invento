import 'dart:ffi';
import 'hel.dart';

class userData {
  late String ID;
  late String PRODUCTNAME;
  late String PRICE;
  late String BRAND;
  late String QUANTITY;

  List<String> l = [];

  userData (String data) {
    l = dataParser(data);

    for (int i = 0; i < l.length; i++) {
      switch (i) {
        case 0:
          ID = l[i];
          break;
        case 1:
          PRODUCTNAME = l[i];
          break;
        case 2:
          PRICE = l[i];
          break;
        case 3:
          BRAND = l[i];
          break;
        case 4:
          QUANTITY = l[i];
          break;
        default:
      }
    }
  }

  List<String> dataParser(String data) {
    List<String> row = [];
    String temp = "";
    for (int i = 0; i < data.length; i++) {
      if (data[i] != '|') {
        temp += data[i];
      } else {
        row.add(temp);
        temp = "";
      }
    }
    if (temp != "") {
      row.add(temp);
    }
    return row;
  }
}

List<userData> getProductData() {
  List<userData> userdata = [];
  Pointer<DatabaseHandler>? dbhandler =
      getSqliteConnection("lib/example.db", "product");
  print(dbhandler.hashCode);
  String data = getDataSqlite(dbhandler, '|');
  while (data != '|') {
    userdata.add(userData(data));
    data = getDataSqlite(dbhandler, '|');
  }
  dbhandler = closeSqliteConnection(dbhandler);
  print(dbhandler.hashCode);
  return userdata;
}
