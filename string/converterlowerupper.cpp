transform(t.begin(), t.end(), t.begin(), [](unsigned char c) {return tolower(c);});
transform(t.begin(), t.end(), t.begin(), [](unsigned char c) {return toupper(c);});
