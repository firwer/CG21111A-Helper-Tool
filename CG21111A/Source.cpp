#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
using namespace std;



string cleanbits(string bits) {
	if (bits.substr(0, 2) == "0b") { //Bits
		if (bits.length() == 10) {
			return bits.substr(2, bits.length());
		}
	}
	else if (bits.substr(bits.length() - 1, 1) == "b") {//Bits
		if (bits.length() == 9) {
			return bits.substr(0, bits.length());
		}
	}
	else {
		return bits;
	}
 }

string getbit() {
	string bits;
	bool invalid = true;
	while (invalid) {
		cout << "Enter the Bits: ";
		cin >> bits;
		bool check = true;
		if (bits.length() == 8) {
			for (auto c : bits) {
				if (c != '1' && c != '0') {
					check = false;
					break;
				}
			}
			if (check) {
				invalid = false;
			}
		}
		if (invalid) {
			cout << "Please try again! Accepted formats: (0b10101010/b10101010/10101010) " << endl;
		}
	}
	bits = cleanbits(bits);
	cout << endl;
	return bits;
}

void getUBRR(unsigned long baudRate, unsigned long F_CPU)
{
	unsigned int b, UBRR0H, UBRR0L;
	UBRR0H = UBRR0L = 0;
	b = (unsigned int)round(F_CPU / (16.0 * baudRate)) - 1;
	UBRR0H = (unsigned char)(b >> 8);
	UBRR0L = (unsigned char)b;
	cout << "UBRR0H = " << UBRR0H << endl;
	cout << "UBRR0L = " << UBRR0L << endl;
}

void getBaud(unsigned long UBRR0, unsigned long F_CPU) {
	unsigned int baudRate;
	baudRate = (unsigned int)round(F_CPU / (16*(UBRR0 + 1)));
	//UBRR0H = (unsigned char)(b >> 8);
	//UBRR0L = (unsigned char)b;
	cout << "Baud Rate = " << baudRate << " bps" << endl;
	//cout << "UBRR0L = " << UBRR0L << endl;
}

int main() {
	unordered_map<string, string> UCSRB({
	{ "0", "Trigger USART_RX_Vect Interrupt when a character is RECEIVED"},
	{ "1", "Trigger USART_TX_Vect Interrupt when finish sending a character"},
	{ "2", "Trigger USART_UDRE_Vect interrupt when sending data register is empty"},
	{ "3", "USART Receiver ENABLED"},
	{ "4", "USART Transmitter ENABLED"},
	{ "5", "Data Bit Size: 1"},
	{ "6", "-"},
	{ "7", "-"} });
	unordered_map<string, string> UCSRC({
	{ "async", "Mode: Asynchronous USART"},
	{ "sync", "Mode: Synchronous USART"},
	{ "reserved", "Mode: Reserved"},
	{ "master", "Mode: Master SPI"},
	{ "disabled", "Parity: DISABLED, N"},
	{ "reservedp", "Parity: Reserved"},
	{ "evenp", "Parity: EVEN PARITY"},
	{ "oddp", "Parity: ODD PARITY"},
	{ "1bit", "STOP BIT: 1 BIT"},
	{ "2bit", "STOP BIT: 2 BIT"},
	{ "5", "Character/Bit Size: 5 Bits"},
	{ "6", "Character/Bit Size: 6 Bits"},
	{ "7", "Character/Bit Size: 7 Bits"},
	{ "8", "Character/Bit Size: 8 Bits"} });
	unordered_map<string, string> EICR({
	{ "low0", "The low level of INT0 generates an interrupt request."},
	{ "change0", "Any logical change on INT0 generates an interrupt request."},
	{ "falling0", "The falling edge of INT0 generates an interrupt request."},
	{ "rising0", "The rising edge of INT0 generates an interrupt request."},
	{ "low1", "The low level of INT1 generates an interrupt request."},
	{ "change1", "Any logical change on INT1 generates an interrupt request."},
	{ "falling1", "The falling edge of INT1 generates an interrupt request."},
	{ "rising1", "The rising edge of INT1 generates an interrupt request."} });
	unordered_map<string, string> ADCS({
	{ "000", "Prescaler Factor: 2"},
	{ "001", "Prescaler Factor: 2"},
	{ "010", "Prescaler Factor: 4"},
	{ "011", "Prescaler Factor: 8"},
	{ "100", "Prescaler Factor: 16"},
	{ "101", "Prescaler Factor: 32"},
	{ "110", "Prescaler Factor: 64"},
	{ "111", "Prescaler Factor: 128"} });
	unordered_map<string, string> TCCR({
	{ "000", "Prescaler Factor: 2"},
	{ "001", "Prescaler Factor: 2"},
	{ "010", "Prescaler Factor: 4"},
	{ "011", "Prescaler Factor: 8"},
	{ "100", "Prescaler Factor: 16"},
	{ "101", "Prescaler Factor: 32"},
	{ "110", "Prescaler Factor: 64"},
	{ "111", "Prescaler Factor: 128"} });
	while (true) {
		cout << "*************** MENU ***************" << endl;
		cout << "Author: Poh Wei Pin @ NUS CEG" << endl;
		cout << "****** PWM Programming ******" << endl;
		cout << "1. TCCR0A/TCCR2A (Timer 0/2)" << endl;
		cout << "2. TCCR0B/TCCR2B (Timer 0/2)" << endl;
		cout << "3. TIMSK" << endl;
		cout << "4. EICRn" << endl;
		cout << "****** USART ******" << endl;
		cout << "5. UCSRnA" << endl;
		cout << "6. UCSRnB" << endl;
		cout << "7. UCSRnC" << endl;
		cout << "8. Calculate Baud Rate from UBBR" << endl;
		cout << "9. Calculate UBBR from Baud Rate" << endl;
		cout << "**Please enter the bits in either format: (0b10101010/b10101010/10101010)" << endl;
		int num, cpuspd;
		string bits;
		cout << "Select (1-9): ";
		cin >> num;
		switch (num) {
		case 1:
			bits = getbit();
			cout << "******Settings for Timer 0 - TCCR0A******" << endl;
			//for OC0A
			if (bits.substr(0, 2) == "00") {
				cout << "Normal Port Operation, OC0A(PIN 6) Disconnected (OC0A is NOT in use)" << endl;
			}
			else if (bits.substr(0, 2) == "01") {
				cout << "Toggle OC0A(PIN 6) on Compare Match (Change Logic 1->0 or 0->1)" << endl;
			}
			else if (bits.substr(0, 2) == "10") {
				cout << "Clear 0C0A(PIN 6) on Compare Match (Set to logic 0)" << endl;
			}
			else if (bits.substr(0, 2) == "11") {
				cout << "Set OC0A(PIN 6) on Compare Match (Set to logic 1" << endl;
			}

			//FOR OC0B
			if (bits.substr(2, 2) == "00") {
				cout << "Normal Port Operation, OC0B(PIN 5) Disconnected (OC0B(PIN 5) is NOT in use)" << endl;
			}
			else if (bits.substr(2, 2) == "01") {
				cout << "Toggle OC0B(PIN 5) on Compare Match (Change Logic 1->0 or 0->1)" << endl;
			}
			else if (bits.substr(2, 2) == "10") {
				cout << "Clear 0C0B(PIN 5) on Compare Match (Set to logic 0)" << endl;
			}
			else if (bits.substr(2, 2) == "11") {
				cout << "Set OC0B(PIN 5) on Compare Match (Set to logic 1" << endl;
			}

			//TIMER WAVE
			if (bits.substr(6, 2) == "00") {
				cout << "Timer Mode: Normal Mode" << endl;
			}
			else if (bits.substr(6, 2) == "01") {
				cout << "Timer Mode: PWM, Phase Correct | Update OCR0A/B at TOP | TOP: 0xFF OR (OCRA/B if TCCRB Wave Generation option is true)" << endl;
			}
			else if (bits.substr(6, 2) == "10") {
				cout << "Timer Mode: CTC (Clear Timer on Compare)" << endl;
			}
			else if (bits.substr(6, 2) == "11") {
				cout << "Timer Mode: Fast PWM | Update OCR0A/B at BOTTOM | TOP: 0xFF OR (OCRA/B if TCCRB Wave Generation option is true)" << endl;
			}
			cout << "******End******" << endl;
			cout << endl;
			break;
		case 2:
			bits = getbit();
			cout << "******Settings for Timer 0 - TCCR0B (Timer starts once prescaler is set!)******" << endl;
			if (bits.substr(5, 3) == "000") {
				cout << "PRESCALER: None (Timer/Counter Stopped)" << endl;
			}
			else if (bits.substr(5, 3) == "001") {
				cout << "PRESCALER: 1" << endl;
			}
			else if (bits.substr(5, 3) == "010") {
				cout << "PRESCALER: 8" << endl;
			}
			else if (bits.substr(5, 3) == "011") {
				cout << "PRESCALER: 64" << endl;
			}
			else if (bits.substr(5, 3) == "100") {
				cout << "PRESCALER: 256" << endl;
			}
			else if (bits.substr(5, 3) == "101") {
				cout << "PRESCALER: 1024" << endl;
			}
			else {
				cout << "PRESCALER: Others" << endl;
			}
			cout << "******End******" << endl;
			cout << endl;
			break;
		case 3:
			bits = getbit();
			cout << "******Settings for Timer n - TIMSKn (Interrupt Mask Register)******" << endl;
			if (bits[5] == '1') {
				cout << "(OCIEB) Output Compare B Match Interrupt ENABLED" << endl;
			}
			if (bits[6] == '1') {
				cout << "(OCIEA) Output Compare A Match Interrupt ENABLED" << endl;
			}
			cout << "******End******" << endl;
			break;
		case 4:
			bits = getbit();
			cout << "******Settings for EICRn******" << endl;
			if (bits.substr(4, 2) == "00") { //INT1
				cout << EICR["low1"] << endl;
			}if (bits.substr(4, 2) == "01") {
				cout << EICR["change1"] << endl;
			}if (bits.substr(4, 2) == "10") {
				cout << EICR["falling1"] << endl;
			}if (bits.substr(4, 2) == "11") {
				cout << EICR["rising1"] << endl;
			}
			else if (bits.substr(6, 2) == "00") { //INT0
				cout << EICR["low1"] << endl;
			}
			else if (bits.substr(6, 2) == "01") {
				cout << EICR["change1"] << endl;
			}
			else if (bits.substr(6, 2) == "10") {
				cout << EICR["falling1"] << endl;
			}
			else if (bits.substr(6, 2) == "11") {
				cout << EICR["rising1"] << endl;
			}
			cout << "******End******" << endl;
			cout << endl;
			break;
		case 5:
			bits = getbit();
			cout << "******Settings for UCSRnA******" << endl;
			if (bits[0] == 1) {
				cout << "USART Receive Complete" << endl;
			}
			else {
				cout << "USART Receive Buffer is Empty" << endl;
			}
			if (bits[1] == 1) {
				cout << "USART Transmit Complete (No data present in the buffer register to transmit)" << endl;
			}
			else {
				cout << "USART Transmit Complete Interrupt is executed" << endl;
			}
			if (bits[2] == 1) {
				cout << "UDRE0 : USART Data Register empty (Transmitter buffer is empty)" << endl;
			}
			else {
				cout << "Transmitter is ready" << endl;
			}
			if (bits[5] == 1) {
				cout << "Next character in the receiver buffer had a Parity Error Detected" << endl;
			}
			else {
				cout << "Writing to UCSR0A" << endl;
			}
			cout << "******End******" << endl;
			cout << endl;
			break;
		case 6:
			bits = getbit();
			cout << "******Settings for UCSRnB******" << endl;
			for (long i = 0; i < bits.length(); i++) {
				if (bits[i] == '1') {
					cout << UCSRB[to_string(i)] << endl;
				}
			}
			cout << "******End******" << endl;
			break;
		case 7:
			bits = getbit();
			cout << "******Settings for UCSRnC******" << endl;
			//Mode
			if (bits.substr(0, 2) == "00") {
				cout << UCSRC["async"] << endl;
			}
			else if (bits.substr(0, 2) == "01") {
				cout << UCSRC["sync"] << endl;
			}
			else if (bits.substr(0, 2) == "10") {
				cout << UCSRC["reserved"] << endl;
			}
			else if (bits.substr(0, 2) == "11") {
				cout << UCSRC["master"] << endl;
			}

			//Parity
			if (bits.substr(2, 2) == "00") {
				cout << UCSRC["disabled"] << endl;
			}
			else if (bits.substr(2, 2) == "01") {
				cout << UCSRC["reservedp"] << endl;
			}
			else if (bits.substr(2, 2) == "10") {
				cout << UCSRC["evenp"] << endl;
			}
			else if (bits.substr(2, 2) == "11") {
				cout << UCSRC["oddp"] << endl;
			}

			//Stop Bit
			if (bits.substr(4, 1) == "0") {
				cout << UCSRC["1bit"] << endl;
			}
			else if (bits.substr(4, 1) == "1") {
				cout << UCSRC["2bit"] << endl;
			}

			//Character size
			if (bits.substr(5, 2) == "00") {
				cout << UCSRC["5"] << endl;
			}
			else if (bits.substr(5, 2) == "01") {
				cout << UCSRC["6"] << endl;
			}
			else if (bits.substr(5, 2) == "10") {
				cout << UCSRC["7"] << endl;
			}
			else if (bits.substr(5, 2) == "11") {
				cout << UCSRC["8"] << endl;
			}
			cout << "******End******" << endl;
			cout << endl;
			break;
		case 8:
			cout << "Baud Rate Calculator" << endl;
			cout << "Enter UBRR0: ";
			int U; cin >> U;
			cout << "Enter CPU Speed (In Hertz) (16MHz = 16000000 Hz): ";
			 cin >> cpuspd;
			getBaud(U, cpuspd);
			cout << endl;
			break;
		case 9:
			cout << "UBRR Baud Calculator, only accept decimal" << endl;
			cout << "Enter Baud Rate (bps): ";
			int baudrate; cin >> baudrate;
			cout << "Enter CPU Speed (In Hertz) (16MHz = 16000000 Hz): ";
			cin >> cpuspd;
			getUBRR(baudrate, cpuspd);
			cout << endl;
			break;
		default:
			cout << "Invalid input, try again" << endl;
			cout << endl;
			break;
		}
	}

}