filename="addressBook.txt"

createBook() {
  numberFormat='^[0-9]+$'
  read -p $'\nNumber of records to create: ' n_records
  echo $'NAME\tCONTACT\tCITY\tSTATE\tZIP\n' > "$filename"
  for((i=0; i<n_records;i++))
  do
    echo -e "\nRecord #`expr $i + 1`"
    read -p "Name: " name
    read -p "Contact Number: " phone
    while grep -q $phone $filename || [ ${#phone} -ne 10 ] || ! [[ $phone =~ $numberFormat ]] || (grep -q "$phone" "$filename")
    do
      read -p "Enter valid and unique Contact Number: " phone
    done
    read -p "City: " city
    read -p "State: " state
    read -p "Zip Code: " zip
    while [ ${#zip} -ne 6 ] || ! [[ $zip =~ $numberFormat ]]
    do
      read -p "Enter valid Zip Code: " zip
    done
    echo -e "$name\t$phone\t$city\t$state\t$zip" >> "$filename"
    echo -e "\nRecord added successfully!"
  done
}

addRecord() {
  read -p $'\nName: ' name
  read -p "Contact Number: " phone
  while [ ${#phone} -ne 10 ] || ! [[ $phone =~ $numberFormat ]] || (grep -q "$phone" "$filename")
  do
    read -p "Enter valid Contact Number: " phone
  done
  read -p "City: " city
  read -p "State: " state
  read -p "Zip Code: " zip
  while [ ${#zip} -ne 6 ] || ! [[ $zip =~ $numberFormat ]]
  do
    read -p "Enter valid Zip Code: " zip
  done
  echo -e "$name\t$phone\t$city\t$state\t$zip" >> "$filename"
  echo -e "\nRecord added successfully!"
}

searchRecord() {
  numberFormat='^[0-9]+$'
  read -p $'\nPhone number to search: ' phone
  if [ ${#phone} -ne 10 ] || ! [[ $phone =~ $numberFormat ]]
  then
    echo $'\nPlease enter a valid phone number.'
  elif (grep -q $phone $filename) # if record exists
  then
    echo $'\nRecord Found!\n'
    (grep -r -w $phone $filename) # display record
  else
    echo $'\nRecord unavailable.'
  fi
}

deleteRecord() {
  numberFormat='^[0-9]+$'
  read -p $'\nPhone number of record to delete: ' phone
  if [ ${#phone} -ne 10 ] || ! [[ $phone =~ $numberFormat ]]
  then
    echo $'\nPlease enter a valid phone number.'
  elif (grep -q $phone $filename)
  then
    echo $'\nDeleted Record: \n'
    (grep -r -w $phone $filename)
    sed -i "/$phone/d" $filename
    sed -i "/^$/d" $filename  # remove empty lines
    echo $'\nRecord deleted successfully.'
  else
    echo $'\nRecord not found.'
  fi
}

modifyRecord() {
  numberFormat='^[0-9]+$'
  read -p $'\nPhone number of record to modify: ' phone
  if [ ${#phone} -ne 10 ] || ! [[ $phone =~ $numberFormat ]]
  then
    echo $'\nPlease enter a valid phone number.'
  elif (grep -q $phone $filename)
  then
    echo $'\nEnter new details:\n'
    read -p $'Name: ' name
    read -p "Contact Number: " newPhone
    while [ ${#newPhone} -ne 10 ] || ! [[ $newPhone =~ $numberFormat ]]
    do
      read -p "Enter valid Contact Number: " newPhone
    done
    read -p "City: " city
    read -p "State: " state
    read -p "Zip Code: " zip
    while [ ${#zip} -ne 6 ] || ! [[ $zip =~ $numberFormat ]]
    do
      read -p "Enter valid Zip Code: " zip
    done
    sed -i "/$phone/c\ $name\t$newPhone\t$city\t$state\t$zip" $filename
  else
    echo $'\nRecord not found.'
  fi
}

displayRecords() {
  if test -f "$filename"
  then
    echo -e "\n"
    while read line
    do
      echo $line
    done <  "$filename"
  else
    echo -e "\nFile not created yet."
  fi
}

sortRecords() {
  if test -f "$filename"
  then
    sort $filename
  else
    echo -e "\nFile not created yet."
  fi
}

# MAIN

resp=1
while [ $resp -ne 8 ]
do
  read -p $'\nAddress Book\n1. Create Book\n2. Add Record\n3. Search Record\n4. Delete Record\n5. Modify Record\n6. Display Records\n7. Display Sorted Records\n8. Exit\nYour Choice: ' resp
  case $resp in
    1) createBook ;;
    2) addRecord ;;
    3) searchRecord ;;
    4) deleteRecord ;;
    5) modifyRecord ;;
    6) displayRecords ;;
    7) sortRecords ;;
    8) ;;
    *) echo $'\nPlease enter a valid response.'
  esac
done
