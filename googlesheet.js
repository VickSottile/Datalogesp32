  function doGet(e) {
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();
  var fecha = new Date();

  // Obtiene parámetros de la URL
  var sensor1 = e.parameter.sensor1;
  var sensor2 = e.parameter.sensor2;

  // Agrega nueva fila
  sheet.appendRow([fecha, sensor1, sensor2]);

  return ContentService.createTextOutput("OK");
}
