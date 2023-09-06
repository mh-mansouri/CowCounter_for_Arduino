#define SIZEIN "SZ"
#define COWIN "CW"
#define TERMINATOR "#"  //SZxxCWxx#
#define SIZEMAX 10

long fieldSize = 1;
long cowNo = 0;
long cowPlace[SIZEMAX - 1][SIZEMAX - 1] = {};
long numberArr[(SIZEMAX * SIZEMAX)] = {};

bool cowArr[(SIZEMAX * SIZEMAX)] = {};

String strIn = "";
String strOut = "";

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));
}

void loop() {
  while (Serial.available()) {
    strIn += Serial.readString();
  }
  if (strIn.indexOf(TERMINATOR) > -1) {
    if (strIn.indexOf(COWIN) > -1) {
      cowNo = strIn.substring(6, 8).toInt();
    }
    if (strIn.indexOf(SIZEIN) > -1) {
      fieldSize = strIn.substring(2, 4).toInt();
    }

    Initialize();
    delay(1000);

    createCowArray();
    delay(1000);

    strOut = "No. of cows in the corners are: " + String(getNumberOfCowsInCorners());
    Serial.println(strOut);
    delay(1000);

    strOut = "No. of adjacent cows are: " + String(getNumberOfCowsWithNeighbours());
    Serial.println(strOut);
    delay(1000);

    strIn = "";
  }
}

void Initialize() {
  long x = 0;
  long y = 0;
  long cowNoHolder = 0;

  strOut = "Initialize the cowArray";
  Serial.println(strOut);
  for (x = 0; x < SIZEMAX; x++) {
    for (y = 0; y < SIZEMAX; y++) {
      cowArr[x + (y * SIZEMAX)] = false;
    }
  }
  delay(1000);

  //fieldSize = random(SIZEMAX) + 1;
  if (fieldSize < 1) {
    fieldSize = 1;
  }
  if (fieldSize > SIZEMAX) {
    fieldSize = SIZEMAX;
  }
  strOut = "The field size is: " + String(fieldSize);
  Serial.println(strOut);
  delay(1000);

  //cowNo = random(fieldSize + 1) * random(fieldSize + 1);
  if (cowNo < 0) {
    cowNo = 0;
  }
  if (cowNo > (fieldSize * fieldSize)) {
    cowNo = (fieldSize * fieldSize) - 1;
  }
  strOut = "The cow no is: " + String(cowNo);
  Serial.println(strOut);
  delay(1000);

  //Initializing the cowplace array with all zero
  strOut = "Initializing the cowplace array with all zero";
  Serial.println(strOut);
  for (x = 0; x < fieldSize; x++) {
    for (y = 0; y < fieldSize; y++) {
      cowPlace[x][y] = 0;
    }
  }
  delay(1000);

  //Distribute the cows randomly
  strOut = "Distribute the cows randomly";
  Serial.println(strOut);
  while (cowNoHolder < cowNo) {
    x = random(fieldSize);
    y = random(fieldSize);
    if (0 == cowPlace[x][y]) {
      cowNoHolder++;
      cowPlace[x][y] = cowNoHolder;
    }
  }
  delay(1000);

  //Diplay the cows on the field
  strOut = "Diplay the cows on the field";
  Serial.println(strOut);
  Serial.println();
  for (x = 0; x < fieldSize; x++) {
    for (y = 0; y < fieldSize; y++) {
      if (cowPlace[x][y]) {
        strOut = String(cowPlace[x][y]) + "\t";
        Serial.print(strOut);
      } else {
        Serial.print(F("X\t"));
      }
    }
    Serial.println();
  }
  delay(1000);
}

void createCowArray() {
  long x = 0;
  long y = 0;
  for (x = 0; x < fieldSize; x++) {
    for (y = 0; y < fieldSize; y++) {
      if (cowPlace[x][y]) {
        cowArr[x + (y * fieldSize)] = true;
      }
      strOut = "("+String(x) + "," + String(y)+"):"+String(cowArr[x + (y * fieldSize)])+"\t";
      Serial.print(strOut);
    }
    Serial.println();
  }
}

long getNumberOfCowsInCorners() {
  long cowsInCorner = 0;
  long corner_0_0 = 0;
  long corner_0_fieldSize = fieldSize - 1;
  long corner_fieldSize_0 = (fieldSize - 1) * fieldSize;
  long corner_fieldSize_fieldSize = (fieldSize * fieldSize) - 1;

  if (fieldSize < 2) {
    return (cowNo);
  }

  if (cowArr[corner_0_0]) {
    cowsInCorner++;
  }

  if (cowArr[corner_0_fieldSize]) {
    cowsInCorner++;
  }

  if (cowArr[corner_fieldSize_0]) {
    cowsInCorner++;
  }

  if (cowArr[corner_fieldSize_fieldSize]) {
    cowsInCorner++;
  }

  return (cowsInCorner);
}

long getNumberOfCowsWithNeighbours() {
  long neighNo = 0;
  long x = 0;
  long y = 0;
  if (fieldSize < 2) {
    return (neighNo);
  }

  for (x = 0; x < fieldSize; x++) {
    for (y = 0; y < fieldSize; y++) {
      if(false == cowArr[x + (y * fieldSize)])
      {
        continue;
      }
      if(x==0)
      {
          if(cowArr[(x+1) + ((y) * fieldSize)])
          {
              neighNo++;
          }
          if(y>0)
          {
              if(cowArr[(x) + ((y-1) * fieldSize)])
              {
                  neighNo++;
              }
          }
          if(y<(fieldSize-1))
          {
              if(cowArr[(x) + ((y+1) * fieldSize)])
              {
                  neighNo++;
              }
          }
      }
      else if(x == (fieldSize - 1))
      {
          if(cowArr[(x-1) + ((y) * fieldSize)])
          {
              neighNo++;
          }
          if(y>0)
          {
              if(cowArr[(x) + ((y-1) * fieldSize)])
              {
                  neighNo++;
              }
          }
          if(y<(fieldSize-1))
          {
              if(cowArr[(x) + ((y+1) * fieldSize)])
              {
                  neighNo++;
              }
          }
      }
      else
      {
          if(cowArr[(x-1) + ((y) * fieldSize)])
          {
              neighNo++;
          }
          if(cowArr[(x+1) + ((y) * fieldSize)])
          {
              neighNo++;
          }
          if(y>0)
          {
              if(cowArr[(x) + ((y-1) * fieldSize)])
              {
                  neighNo++;
              }
          }
          if(y<(fieldSize-1))
          {
              if(cowArr[(x) + ((y+1) * fieldSize)])
              {
                  neighNo++;
              }
          }

      }

    }
  }
  return (neighNo);
}
