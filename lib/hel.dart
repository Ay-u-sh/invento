import 'dart:ffi';
import 'package:ffi/ffi.dart';

final dylib = DynamicLibrary.open('libdesign.dll');
int tryLimit = 10;

final class DatabaseHandler extends Struct {
  external Pointer<DatabaseHandler> p;
}

typedef GetSqliteConnectionC = Pointer<DatabaseHandler> Function(
    Pointer<Utf8>, Pointer<Utf8>);
typedef GetSqliteConnectionDart = Pointer<DatabaseHandler> Function(
    Pointer<Utf8>, Pointer<Utf8>);

Pointer<DatabaseHandler> getSqliteConnection(
    String dbfilename, String tablename) {
  Pointer<Utf8> fn = dbfilename.toNativeUtf8();
  Pointer<Utf8> tb = tablename.toNativeUtf8();
  final GetSqliteConnectionDart getSqliteConnectionDart =
      dylib.lookupFunction<GetSqliteConnectionDart, GetSqliteConnectionC>(
          'getSQLiteConnection');
  return getSqliteConnectionDart(fn, tb);
}

typedef GetDataSqliteC = Pointer<Utf8> Function(
    Pointer<DatabaseHandler>, Pointer<Utf8>);
typedef GetDataSqliteDart = Pointer<Utf8> Function(
    Pointer<DatabaseHandler>, Pointer<Utf8>);

String getDataSqlite(Pointer<DatabaseHandler> dbhandler, String separator) {
  Pointer<Utf8> sep = separator.toNativeUtf8();
  final GetDataSqliteDart getDataSqliteDart =
      dylib.lookupFunction<GetDataSqliteC, GetDataSqliteDart>('getTableData');

  return getDataSqliteDart(dbhandler, sep).toDartString();
}

typedef CloseSqliteConnectionC = Pointer<DatabaseHandler> Function(
    Pointer<DatabaseHandler>);
typedef CloseSqliteConnectionDart = Pointer<DatabaseHandler> Function(
    Pointer<DatabaseHandler>);

Pointer<DatabaseHandler> closeSqliteConnection(
    Pointer<DatabaseHandler> dbhandler) {
  final CloseSqliteConnectionDart closeSqliteConnectionDart =
      dylib.lookupFunction<CloseSqliteConnectionC, CloseSqliteConnectionDart>(
          'closeSQLiteConnection');
  return closeSqliteConnectionDart(dbhandler);
}

typedef InsertCSVSqliteC = Bool Function(
    Pointer<Utf8>, Pointer<Utf8>, Pointer<Utf8>);
typedef InsertCSVSqliteDart = bool Function(
    Pointer<Utf8>, Pointer<Utf8>, Pointer<Utf8>);

bool insertCSVSqlite(String filename, String dbfilename, String tablename) {
  Pointer<Utf8> fn = filename.toNativeUtf8();
  Pointer<Utf8> db = tablename.toNativeUtf8();
  Pointer<Utf8> tn = tablename.toNativeUtf8();

  final InsertCSVSqliteDart insertCSVSqliteDart = dylib
      .lookupFunction<InsertCSVSqliteC, InsertCSVSqliteDart>('insertCSVSqlite');

  return insertCSVSqliteDart(fn, db, tn);
}

typedef GetTopSellingDataSqliteC = Pointer<Utf8> Function(
    Pointer<DatabaseHandler>, Pointer<Utf8>);
typedef GetTopSellingDataSqliteDart = Pointer<Utf8> Function(
    Pointer<DatabaseHandler>, Pointer<Utf8>);

String getTopSellingDataSqlite(
    Pointer<DatabaseHandler> dbhandler, String separator) {
  Pointer<Utf8> sep = separator.toNativeUtf8();

  final GetTopSellingDataSqliteDart getTopSellingDataSqliteDart = dylib
      .lookupFunction<GetTopSellingDataSqliteC, GetTopSellingDataSqliteDart>(
          'getTopSellingData');
  return getTopSellingDataSqliteDart(dbhandler, sep).toDartString();
}

typedef GetLowStockSqliteC = Pointer<Utf8> Function(
    Pointer<DatabaseHandler>, Int32, Pointer<Utf8>);
typedef GetLowStockSqliteDart = Pointer<Utf8> Function(
    Pointer<DatabaseHandler>, int, Pointer<Utf8>);

String getLowStockDataSqlite(
    Pointer<DatabaseHandler> dbhandler, int limit, String separator) {
  Pointer<Utf8> sep = separator.toNativeUtf8();

  final GetLowStockSqliteDart getLowStockSqliteDart =
      dylib.lookupFunction<GetLowStockSqliteC, GetLowStockSqliteDart>(
          'getLowStockData');

  return getLowStockSqliteDart(dbhandler, limit, sep).toDartString();
}
