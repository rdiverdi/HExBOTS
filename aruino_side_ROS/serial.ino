void read_line(char *line) {
    // read characters from serial into line until a newline character
    char c;
    int index;
    int message_index=0;
    int angles_index=0;
    for (index = 0; index < 50; index++) {
        // wait until there is a character
        while (Serial.available() == 0);
        Serial.println(0);
        // read a character
        c = Serial.read();
        if (c == '\n') {
            line[index] = '\0';
            angles_index = angles_index + parse_message(line, angles_index);
            break;
        }
        else if (c == ',') {
          line[index] = '\0';
          index = -1;
          angles_index = angles_index + parse_message(line, angles_index);
        }
        else {
            line[index] = c;
        }
    }
    if (angles_index != 18){
      Serial.println(1);
    }
    // terminate the string
}

int get_amount(char *line) {
    // return the number in a string such as "r1200" as an int
    int amount;
    amount = (int) strtol(line+1, NULL, 10);
    return amount;
}

int parse_message(char *message, int index) {
    switch (message[0]) {
      case 'a': //angles data:
        angles[index] = get_amount(message);
        return 1;
    }
    return 0;
}

