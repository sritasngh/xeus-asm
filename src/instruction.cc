/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file    instruction.cc
 * @brief   contains implementation for all the 8085 instructions
 */

#include "xasm/instruction.hpp"

void ADD(string arg1, string registers[], bool flag[],
         map<string, string> &memory) {

  int length = arg1.length();
  if (length == 1) {

    if (validityRegisters(arg1) || validityRegisterPair(arg1)) {

      if (arg1 != "M") {

        /*Fetches index of register to access array string registers[]*/
        int registerID = registerNumber(arg1);
        /*Converting decimal value to string format and storing in accumulator*/
        registers[0] = hexAdd(registers[registerID], registers[0], flag, true);

      } else {

        /*Fetches data of HL pair*/
        string address = "";
        address = address + registers[5] + registers[6];
        if (address >= "0000" && address <= "FFFF") {

          /*Converting decimal value to string format and storing in
           * accumulator*/
          registers[0] = hexAdd(memory[address], registers[0], flag, true);
        } else {

          cout << "Error: " << arg1 << "\n";
          cout << "Address out of bounds\nThe program will quit\n";
          exit(0);
          /*error message of address out of bounds*/
        }
      }
    } else {

      cout << "Error: " << arg1
           << "\nInvalid register details\nThe program will quit\n";
      exit(0);
      /*error of invalid register details*/
    }
  } else {

    cout << "Error: " << arg1 << "\nInvalid arguments\nThe program will quit\n";
    exit(0);
    /*Error message of invalid arguments*/
  }
}

void MOV(string argument1, string argument2, string registers[], bool flag[],
         map<string, string> &memory) {
  int l1 = argument1.length();
  int l2 = argument2.length();
  if (l1 == 1 && l2 == 1) {
    if (argument1 == "M" && argument2 != "M" && validityRegisters(argument2)) {
      string address = registers[5] + registers[6];
      memory[address] = registers[registerNumber(argument2)];
    } else if (argument1 != "M" && argument2 == "M" &&
               validityRegisters(argument1)) {
      string address = registers[5] + registers[6];
      registers[registerNumber(argument1)] = memory[address];
    } else if (argument1 != "M" && argument2 != "M" &&
               validityRegisters(argument2) && validityRegisters(argument1)) {
      registers[registerNumber(argument1)] =
          registers[registerNumber(argument2)];
    } else {
      cout << "Error: "
           << "Invalid content\nThe program will quit\n";
      exit(0);
    }
  }
}

void MVI (string arg1,string arg2,string registers[],bool flags[],map<string,string> &memory){
	int l1=arg1.length();
	int l2=arg2.length();
	if(l1==1&&l2==2){
        	if(arg1=="M"){
            		string address=registers[5]+registers[6];
            		if(validityData(arg2))
                		memory[address]=arg2;
            		else{
				cout<<"Error: "<<"Invalid content\nThe program will quit\n";
				exit(0);
				}
        	}
		else if(validityRegisters(arg1)&&validityData(arg2)){	
			registers[registerNumber(arg1)] = arg2;
		}
		else{
			cout<<"Error: "<<"Invalid content\nThe program will quit\n";
			exit(0);
		}
	}
	else{
		cout<<"Error: "<<"Invalid content\nThe program will quit\n";
		exit(0);
	}
}

void ADI(string arg, string registers[],bool flag[]){

	int length = arg.length();
	if(length == 2){
	
		if(validityData(arg)){
			
			/*Performs immediate addition and stores in accumulator*/
			registers[0] = hexAdd(arg,registers[0],flag,true);
		}
		else{
			
			cout<<"Error: "<<arg<<"\nInvalid data content\nThe program will quit\n";
			exit(0);
			/*Error message of invalid data content*/
		}
	}
	else{
		
		cout<<"Error: "<<arg<<"\nInvalid data size\nThe program will quit\n";
		exit(0);
		/*Error message of invalid data size*/
	}
	
}

void SUB(string arg1,string registers[],bool flag[],map<string,string>&memory){
	
	int length=arg1.length();
	if(length == 1){
		
		if(validityRegisters(arg1)){
			
			if(arg1 != "M"){
			
				/*Fetches index of register to access array string registers[]*/
				int registerID = registerNumber(arg1);              
				/*Converting decimal value to string format and storing in accumulator*/
				registers[0] = hexSub(registers[registerID],registers[0],flag,true);
				
			}
			else{                         
		
				/*Fetches data of HL pair*/
				string address = "";
				address = address + registers[5] + registers[6];
				if(address >= "0000" && address <= "FFFF"){
				
					/*Converting decimal value to string format and storing in accumulator*/
					registers[0] = hexSub(memory[address],registers[0],flag,true);				
					
				}
				else{
					cout<<"Error: "<<arg1<<"\nAddress out of bounds\nThe program will quit\n";
					exit(0);
					/*error message of address out of bounds*/
				}						
			}
		}
		else{
			cout<<"Error: "<<arg1<<"\nInvalid register details\nThe program will quit\n";
			exit(0);
			/*error of invalid register details*/
		}
	}
	else{
		cout<<"Error: "<<arg1<<"\nInvalid arguments\nThe program will quit\n";
		exit(0);
		/*Error message of invalid arguments*/
	}
}

void DAD(string arg,string registers[],bool flag[]){

	int length = arg.length();
	if(length == 1){
	
		if(validityRegisters(arg)){
		
			int registerID = registerNumber(arg);
			if(registerID == 1 || registerID == 3 || registerID == 5){
				
				string data16bit = "";
				string data16bitHL = "";
				string resultant = "";
				if(validityData(registers[registerID]) && validityData(registers[registerID+1]) && validityData(registers[5]) && validityData(registers[6])){
				
					data16bit = data16bit + registers[registerID] + registers[registerID];
					data16bitHL = data16bitHL + registers[5] + registers[6];
					int value16bit[4];
					int value16bitHL[4];
					int carry = 0;
					hexToDecimal(arg,value16bit);
					hexToDecimal(arg,value16bitHL);	  
					for(int i = 3;i>=0;i--){
					
						int value = value16bit[i] + value16bitHL[i] + carry;
						if(value >= 16)
							flag[0] = true;
						else
							flag[0] = false;
						carry = value / 16;
						value = value % 16;
						if(value>=0 && value<=9)
							resultant = (char)('0' + value) + resultant;
						else{
							switch(value){
							
								case 10:
									resultant = "A" + resultant;
									break;
								case 11:
									resultant = "B" + resultant;
									break;
								case 12:
									resultant = "C" + resultant;
									break;
								case 13:
									resultant = "D" + resultant;
									break;
								case 14:
									resultant = "E" + resultant;
									break;
								case 15:
									resultant = "F" + resultant;
									break;	
							}
						}
					}
					
					registers[5] = resultant[0] + resultant[1];
					registers[6] = resultant[2] + resultant[3];	
				}		
				else{
					cout<<"Error: "<<arg<<"\nInvalid data content in registet\nThe program will quit\n";
					exit(0);
					/*Error:Invalid data content in registers*/
				}
			}
			else{
				cout<<"Error: "<<arg<<"\nInvalid register pair\nThe program will quit\n";
				exit(0);
				/*Error:Invaid register pair*/
			}
		}
		else{
			cout<<"Error: "<<arg<<"\nInvalid register content\nThe program will quit\n";
			exit(0);
			/*Error:Invalid register content*/ 
		}
	}
	else{
		cout<<"Error: "<<arg<<"\nInvalid arguments\nThe program will quit\n";
		exit(0);
		/*Error:Invalid Input Argument*/
	}
}

void INR(string arg,string registers[],bool flag[],map<string,string>&memory){

	int length = arg.length();
	if(length == 1){
	
		if(validityRegisters(arg)){
		
			if(arg != "M"){
				
				/*Performs INR on a register*/
				int registerID = registerNumber(arg);
				registers[registerID] = hexAdd(registers[registerID],"01",flag,false); 
			}
			else{
				/*Performs DCR on HL pair*/
				string address = "";
				address = address + registers[5] + registers[6];
				if(validityAddress(address)){
				
					memory[address] = hexAdd(memory[address],"01",flag,false);
				}
				else{
					
					cout<<"Error: "<<arg<<"\nAddress out of bounds\nThe program will quit\n";
					exit(0);
				}
			}
		}
		else{
			
			cout<<"Error: "<<arg<<"\nInvalid register details\nThe program will quit\n";
			exit(0);
			/*Error:Invalid Register*/
		}
	}
	else{
		
		cout<<"Error: "<<arg<<"\nInvalid argument type\nThe program will quit\n";
		exit(0);
		/*Error: Invalid argument type*/
	}
}

void INX(string arg,string registers[],bool flag[]){

	int length = arg.length();
	if(length == 1){
	
		if(validityRegisters(arg)){
			
			int registerID = registerNumber(arg);
			if(registerID == 1 || registerID == 3 || registerID == 5){
			
				string data16bit = "";
				string temporary = "";	
				string s1 = "";
				string s2 = "";
				if(validityData(registers[registerID]) == true && validityData(registers[registerID+1]) == true){
					
					data16bit = data16bit + registers[registerID] + registers[registerID + 1];
					//temporary =  hexAdd16bit(data16bit,"0001",flag,false);
					temporary = increaseAddress(data16bit);
					 s1 = s1 + temporary[0] + temporary[1];		
					 s2 = s2 + temporary[2] + temporary[3];
					 registers[registerID] = s1; 
					 registers[registerID+1] = s2;
				}
				else{
					
					cout<<"Error: "<<arg<<"\nInvalid data content in registers\nThe program will quit\n";
					exit(0);
					/*Error:Invalid data content in registers*/
				}
			}
			else{
				cout<<"Error: "<<arg<<"\nInvalid register pair\nThe program will quit\n";
				exit(0);
				/*Error:Invaid register pair*/
			}
		}
		else{
			cout<<"Error: "<<arg<<"\nInvalid register content\nThe program will quit\n";
			exit(0);
			/*Error:Invalid register content*/ 
		}
	}
	else{
		cout<<"Error: "<<arg<<"\nInvalid input arguments\nThe program will quit\n";
		exit(0);
		/*Error:Invalid Input Argument*/
	}
}

void CMA(string registers[],bool flags[])
{
	string complment = complement(registers[0]);
	registers[0] = complment;
	if(registers[0]=="00")
    {
        flags[6] = true;
        flags[2] = true;
    }
    else
    {
        string temp = registers[0];
		int array[2];
		hexToDecimal(temp,array);
		int value=array[1]*16+array[0];
		bitset<8> dataInBinary(value);
		int parity = dataInBinary.count();
		if(parity%2 == 0 && parity!=0)
			flags[2] = true;
		else
			flags[2] = false;
    }
}

void CMP (string arg1,string registers[],bool flag[],map<string,string> &memory)
{
	int l1=arg1.length();
	if(l1==1)
	{
		if(arg1=="M")
		{
		    string address=registers[5]+registers[6];
			if(registers[0]<memory[address])
			{
			    flag[0]=true;
			}
			else if(registers[0]==memory[address])
			{
				flag[6]=true;
				//cout<<"zero set\n";
			}
			else
			{
				//cout<<"both reset\n";
				flag[0]=false;
				flag[6]=false;
			}
		}
		else if(validityRegisters(arg1))
		{
			int index=registerNumber(arg1);
    		if(registers[0]<registers[index])
    		{
				//cout<<"carry set\n";
				flag[0]=true;
			}
			else if(registers[0]==registers[index])
			{
				//cout<<"zero set\n";
				flag[6]=true;
			}
			else
			{
				//cout<<"both reset\n";
			    flag[0]=false;
				flag[6]=false;
			}
		}
		else{
			
			cout<<"Error: "<<arg1<<"\nInvalid registers\nThe program will quit\n";
			exit(0);
		}
	}
	else{
		
		cout<<"Error: "<<arg1<<"\nInvalid argument\nThe program will quit\n";
		exit(0);
	}
}

void DCR(string arg,string registers[],bool flag[],map<string,string>&memory){

	int length = arg.length();
	if(length == 1){
	
		if(validityRegisters(arg)){
		
			if(arg != "M"){
				
				/*Performs INR on a register*/
				int registerID = registerNumber(arg);
				registers[registerID] = hexSub(registers[registerID],"01",flag,false);
			}
			else{
				/*Performs DCR on HL pair*/
				string address = "";
				address = address + registers[5] + registers[6];
				if(validityAddress(address)){
				
					memory[address] = hexSub(memory[address],"01",flag,false);
				}
				else{
					cout<<"Error: "<<arg<<"\nInvalid register details\nThe program will quit\n";
					exit(0);
					/*Error:Address out of bounds*/
				}
			}
		}
		else{
			cout<<"Error: "<<arg<<"\nInvalid register\nThe program will quit\n";
			exit(0);
			/*Error:Invalid Register*/
		}
	}
	else{
		
		cout<<"Error: "<<arg<<"\nInvalid argument\nThe program will quit\n";
				exit(0);
		/*Error: Invalid argument type*/
	}
}

void DCX(string arg,string registers[],bool flag[]){

	int length = arg.length();
	if(length == 1){
	
		if(validityRegisters(arg)){
			
			int registerID = registerNumber(arg);
			if(registerID == 1 || registerID == 3 || registerID == 5){
			
				string data16bit = "";
				string temporary = "";
				string s1 = "";
				string s2 = "";
				if(validityData(registers[registerID]) == true && validityData(registers[registerID+1]) == true){
					
					data16bit = data16bit + registers[registerID] + registers[registerID + 1];
					temporary = hexSub16bit(data16bit,"0001",flag,false);
					 s1 = s1 + temporary[0] + temporary[1];		
					 s2 = s2 +temporary[2] + temporary[3];
					registers[registerID] = s1;
					registers[registerID+1] = s2;
				}
				else{
					cout<<"Error: "<<arg<<"\nInvalid data content\nThe program will quit\n";
					exit(0);
					/*Error:Invalid data content in registers*/
				}
			}
			else{
				cout<<"Error: "<<arg<<"\nInvalid register pair\nThe program will quit\n";
				exit(0);
				/*Error:Invaid register pair*/
			}
		}
		else{
			cout<<"Error: "<<arg<<"\nInvalid register content\nThe program will quit\n";
			exit(0);
			/*Error:Invalid register content*/ 
		}
	}
	else{
		cout<<"Error: "<<arg<<"\nInvalid input arguments\nThe program will quit\n";
		exit(0);
		/*Error:Invalid Input Argument*/
	}
}

string JC(string arg, string programCounter, string Registers[],bool flag[]){

	if(flag[0] == true)
		return arg;
	else{
		
		string resultant = "";
		int value16bit[4];
		int returnValue[] = {0,0,0,3};
		int carry = 0;
		hexToDecimal(programCounter,value16bit);	  
		for(int i = 3;i>=0;i--){
					
			int value = value16bit[i] + returnValue[i] + carry;
			carry = value / 16;
			value = value % 16;
			if(value>=0 && value<=9)
				resultant = (char)('0'+value) + resultant;
			else{
				resultant = (char)('A'+(value-10)) + resultant;
			}
		}
		if(validityAddress(resultant))
			return resultant;
		else{
			
			cout<<"Error: "<<arg<<"\nAddress overflow\nThe program will quit\n";
				exit(0);
		}
	}
}

string JMP(string arg, string Registers[],bool flag[]){

	if(validityAddress(arg))
		return arg;
	else{
		
		cout<<"Error encountered in: "<<arg<<"\n";
		cout<<"The program will quit\n";
		exit(0);
	}
}

string JNC(string arg, string programCounter, string Registers[],bool flag[]){

	if(flag[0] == false)
		return arg;
	else{
		
		string resultant = "";
		int value16bit[4];
		int returnValue[] = {0,0,0,3};
		int carry = 0;
		hexToDecimal(programCounter,value16bit);	  
		for(int i = 3;i>=0;i--){
					
			int value = value16bit[i] + returnValue[i] + carry;
			carry = value / 16;
			value = value % 16;
			if(value>=0 && value<=9)
				resultant = (char)('0' + value) + resultant;
			else{
				resultant = (char)('A' + (value-10)) + resultant;
			}
		}
		if(validityAddress(resultant))
			return resultant;
		else
		{
			cout<<"Error: "<<arg<<"\nAdress overflow\nThe program will quit\n";
				exit(0);
		}
			/*Error - Address over-flow*/
	}
}

string JNZ(string arg, string programCounter, string Registers[],bool flag[]){

	if(flag[6] == false){
		
		return arg;
	}
	else{

		string resultant = "";
		int value16bit[4];
		int returnValue[] = {0,0,0,3};
		int carry = 0;
		hexToDecimal(programCounter,value16bit);	  
		for(int i = 3;i>=0;i--){
					
			int value = value16bit[i] + returnValue[i] + carry;
			carry = value / 16;
			value = value % 16;
			if(value>=0 && value<=9)
				resultant = (char)('0' + value) + resultant;
			else{
				resultant = (char)('A'+(value-10)) + resultant;
			}
		}
		if(validityAddress(resultant))
			return resultant;
		else
		{
			cout<<"Error: "<<arg<<"\nAddress overflow\nThe program will quit\n";
				exit(0);
			}
			/*Error - Address over-flow*/
	}
}

string JZ(string arg, string programCounter, string Registers[],bool flag[]){

	if(flag[6] == true)
		return arg;
	else{
		
		string resultant = "";
		int value16bit[4];
		int returnValue[] = {0,0,0,3};
		int carry = 0;
		hexToDecimal(programCounter,value16bit);	  
		for(int i = 3;i>=0;i--){
					
			int value = value16bit[i] + returnValue[i] + carry;
			carry = value / 16;
			value = value % 16;
			if(value>=0 && value<=9)
				resultant = (char)('0' + value) + resultant;
			else{
				resultant = (char)('A'+(value-10)) + resultant;
			}
		}
		if(validityAddress(resultant))
			return resultant;
		else
		{
			cout<<"Error: "<<arg<<"\nAddress overflow\nThe program will quit\n";
				exit(0);
		}
			/*Error - Address over-flow*/
	}
}

void LDA (string arg1,string registers[],bool flag[],map<string,string> &memory)
{
	int l1=arg1.length();
	if(l1==4)
	{
		if(validityAddress(arg1)){

			registers[0] = memory[arg1];
		}
		else
		{
			cout<<"Error: "<<arg1<<"\nInvalid address\nThe program will quit\n";
				exit(0);
		}
	}
	else
	{
		cout<<"Error: "<<arg1<<"\nInvalid arguments\nThe program will quit\n";
				exit(0);
	}
}

void LHLD (string arg1,string registers[],bool flag[],map<string,string> &memory)
{
	int l1=arg1.length();
	if(l1==4)
	{
		if(validityAddress(arg1)&&validityAddress(increaseAddress(arg1)))
		{
			registers[6]=memory[arg1];
			registers[5]=memory[increaseAddress(arg1)];
		}
		else 
		{
			cout<<"Error: "<<arg1<<"\nSome error is thrown\nThe program will quit\n";
				exit(0);
		}
	}
	else
	{
		cout<<"Error: "<<arg1<<"\nInvalid arguments\nThe program will quit\n";
				exit(0);
	}
}

void LXI (string arg1,string arg2,string registers[],bool flags[],map<string,string> &memory)
{
	int l1=arg1.length();
	int l2=arg2.length();
	if(l1==1&&l2==4)
	{
		if(arg1=="M")
		{
			if(validityAddress(arg2))
			{
				string part1="",part2="";
				for(int i=0;i<2;i++)
				{
					part1+=arg2[i];
					part2+=arg2[i+2];
				}
				registers[5]=part1;
				registers[6]=part2;
			}
			else
			{
				cout<<"Error: "<<arg1<<" & "<<arg2<<"\nInvalid content\nThe program will quit\n";
				exit(0);
			}
		}
		else
		{
			if(validityRegisterPair(arg1)&&validityAddress(arg2))
			{
				string part1="",part2="";
				for(int i=0;i<2;i++)
				{
					part1+=arg2[i];
					part2+=arg2[i+2];
				}
				registers[registerNumber(arg1)]=part1;
				registers[registerNumber(arg1)+1]=part2;
			}
			else
			{
				cout<<"Error: "<<arg1<<" & "<<arg2<<"\nInvalid content\nThe program will quit\n";
				exit(0);
			}
		}
	}
	else
	{
		cout<<"Error: "<<arg1<<" & "<<arg2<<"\nInvalid arguments\nThe program will quit\n";
				exit(0);
		}
}

void SET(string arg1,string arg2,map<string,string> &memory){
	int l1=arg1.length();
	int l2=arg2.length();
	if(l1==4 && l2==2 && validityAddress(arg1)&&validityData(arg2))
		memory[arg1]=arg2;
	else{
		cout<<"Error: "<<arg1<<" & "<<arg2<<"\nInvalid arguments\nThe program will quit\n";
		exit(0);
	}
}

void SHLD (string arg1, string registers[],bool flag[], map<string,string> &memory){
	int l1=arg1.length();
	if(l1 == 4 && validityAddress(arg1) && registers[5]!="" && registers[6]!="" && memory.empty() == false){
		memory[arg1]=registers[6];
		memory[increaseAddress(arg1)]=registers[5];
	}
	else{
		cout<<"Error: "<<arg1<<"\nInvalid content\nThe program will quit\n";
	}
}

void STA (string arg1,string registers[],bool flag[],map<string,string> &memory)
{
	int l1=arg1.length();
	if(l1==4)
	{
		if(validityAddress(arg1))
			memory[arg1]=registers[0];
		else
		{
			cout<<"Error: "<<arg1<<"\nInvalid address\nThe program will quit\n";
			exit(0);
		}
	}
	else
	{
		cout<<"Error: "<<arg1<<"\nInvalid arguments\nThe program will quit\n";
		exit(0);
	}
}

void STAX(string arg1,string registers[],bool flag[],map<string,string> &memory)
{
	int l1=arg1.length();
	if(l1==1)
	{
		if(validityRegisterPair(arg1))
		{
			string address="";
			int index=registerNumber(arg1);
			address+=registers[index]+registers[index+1];
			if(validityAddress(address))
				memory[address]=registers[0];
			else
			{
				cout<<"Error: "<<arg1<<"Invalid address\nThe program will quit\n";
				exit(0);
			}
		}
		else
		{
			cout<<"Error: "<<arg1<<"\nInvalid register pair\nThe program will quit\n";
			exit(0);
		}
	}
	else
	{
		cout<<"Error: "<<arg1<<"\nInvalid content\nThe program will quit\n";
		exit(0);
	}
}

void SUI(string arg, string registers[],bool flag[]){

	int length = arg.length();
	if(length == 2){
	
		if(validityData(arg)){
			
			/*Performs immediate subtraction and stores in accumulator*/
			registers[0] = hexSub(arg,registers[0],flag,true);
		}
		else{
			
			cout<<"Error: "<<arg<<"\n";
			cout<<"This is an invalid data\n";
			exit(0);
			/*Error message of invalid data content*/
		}
	}
	else{
		
		cout<<"Error: "<<arg<<"\n";
		cout<<"You have tried to enter invalid data\nThe program will quit\n";
		exit(0);
		/*Error message of invalid data size*/
	}
	
}

void XCHG (string registers[],bool flag[])
{
	string temp=registers[3];
	registers[3]=registers[5];
	registers[5]=temp;
	temp=registers[4];
	registers[4]=registers[6];
	registers[6]=temp;
}