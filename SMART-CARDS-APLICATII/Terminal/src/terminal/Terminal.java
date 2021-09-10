package terminal;

import com.sun.javacard.apduio.*;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.io.BufferedReader;
import java.io.FileReader;
import java.lang.Integer;
import java.util.Arrays;
import java.util.Scanner;

public class Terminal {
	// cvm-urile si conditiile acceptate de terminal
	private byte[] supportedCVM;
	private byte[] supportedCVR;
	
	// campurile v1, v2 si lista cvm obtinuta de pe card
	private byte V1, V2;
	private byte[][] CVM;
	
	private CadClientInterface cad;
	private Socket sock;
	private InputStream is;
	private OutputStream os;
	
	public Terminal() {
		supportedCVM = new byte[] {
//			0b0000_0001, 0b0100_0001, // plaintext pin verificat de sc
			0b0000_0010, 0b0100_0010, // pin criptat verificat online
			0b0000_0011, 0b0100_0011, // plaintext pin verificat de sc si semnatura
			0b0000_0100, 0b0100_0100, // pin criptat verificat de sc
			0b0000_0101, 0b0100_0101, // pin criptat verificat de sc si semnatura
			0b0001_1110, 0b0101_1110, // semnatura
//			0b0001_1111, 0b0101_1111 // nu necesita cvm
		};
		
		supportedCVR = new byte[] {
			0x0, // mereu
			0x1, // numerar nesupravegheat
			0x2, // numerar supravegheat dar tranzactie fara cashback
			0x3, // terminalul accepta CVM-ul 
			0x5, // tranzactie cu cashback
			0x6, // tranzactia foloseste valuta acceptata de aplicatie si e <= V1
			0x7, // tranzactia foloseste valuta acceptata de aplicatie si e > V1
			0x8, // tranzactia foloseste valuta acceptata de aplicatie si e <= V2
			0x9 // tranzactia foloseste valuta acceptata de aplicatie si e > V2
		};
	}
	
	public static void main(String[] args) {
		Terminal terminal = new Terminal();
		
		boolean connected = false;
		while (!connected) {
			try {
				// initializare simulator
				terminal.Start();
				terminal.Connect();
				
				// initializare card
				terminal.Install();
				terminal.Create();
				terminal.Select();
				terminal.GetCVM();
				
				// interactiune cu cardholder-ul
				terminal.Input();
				
				terminal.Close();

				connected = true;
			} catch (IOException | CadTransportException e) {
				System.out.println(e);
			}			
		}
	}
	
	private void Start() throws IOException {
		Log("Pornesc simulatorul...");
		
		String cref = "D:\\Utilitare\\JCDK\\bin\\cref.bat";
		Runtime.getRuntime().exec(cref);
		
		Log("Am pornit simulatorul!\n");
	}
	
	private void Connect() throws UnknownHostException, IOException, CadTransportException {
		Log("Ma conectez la simulator...");
		
		sock = new Socket("localhost", 9025);

		is = sock.getInputStream();
		os = sock.getOutputStream();

		cad = CadDevice.getCadClientInstance(CadDevice.PROTOCOL_T1, is, os);

		byte[] atr = cad.powerUp();
		
		Log("M-am conectat la simulator!\n");
	}
	
	private void Close() throws IOException, CadTransportException
	{
		Log("Inchid simulatorul...");
		
		cad.powerDown();
		
		Log("Am inchis simulatorul!\n");
	}
	
	private void Install() throws IOException, CadTransportException {
		Log("Instalez cardul...");
		
		String script = "D:\\Diverse\\Facultate\\sca\\Wallet\\apdu_scripts\\cap-Wallet.script";

		BufferedReader bufferedReader = new BufferedReader(new FileReader(script));
		String line;
		
		// procesez fisierul linie cu linie
		while ((line = bufferedReader.readLine()) != null) {
			// procesez doar comenzile apdu
			if (line.startsWith("0x")) {
				Process(line);
			}
		}
		bufferedReader.close();
		
		Log("Am instalat cardul!\n");
	}
	
	private void Create() throws IOException, CadTransportException {
		Log("Creez cardul...");
		
		String command = "0x80 0xB8 0x00 0x00 0x14 0x0a 0xa0 0x0 0x0 0x0 0x62 0x3 0x1 0xc 0x6 0x1 0x08 0x0 0x0 0x05 0x01 0x02 0x03 0x04 0x05 0x7F;";
		Process(command);
		
		Log("Am creat cardul!\n");
	}
	
	private void Select() throws IOException, CadTransportException {
		Log("Selectez cardul...");
		
		String command = "0x00 0xA4 0x04 0x00 0x0a 0xa0 0x0 0x0 0x0 0x62 0x3 0x1 0xc 0x6 0x1 0x7F;";
		Process(command);
		
		Log("Am selectat cardul!\n");
	}
	
	private Apdu Process(String line) throws IOException, CadTransportException {
		line = line.replace(";", ""); // inlatur ";" de la sfarsit
		line = line.replace("0x", ""); // inlatura marcajul "0x" de peste tot

		String[] bytes = line.split(" "); 

		byte[] command = {
			(byte) Integer.parseInt(bytes[0], 16), // cla
			(byte) Integer.parseInt(bytes[1], 16), // ins
			(byte) Integer.parseInt(bytes[2], 16), // p1
			(byte) Integer.parseInt(bytes[3], 16) // p2
		};
		
		byte lc = (byte) Integer.parseInt(bytes[4], 16);
		byte[] data = new byte[lc];
		
		for (int i = 0; i < lc; i++) {
			data[i] = (byte) Integer.parseInt(bytes[i+5], 16);
		}
		
		byte le = (byte) Integer.parseInt(bytes[bytes.length - 1], 16);
		
		Apdu apdu = new Apdu();
		
		// configurez structura apdu
		apdu.command = command;				
		apdu.setDataIn(data, lc);
		apdu.Le = le;
		
		Request(apdu); // afisez in consola structura apdu ce urmeaza a fi trimisa catre card
		
		cad.exchangeApdu(apdu);
		
		Response(apdu); // afisez in consola structura apdu primita ca raspuns
		
		return apdu;
	}
	
	private void Input() throws IOException, CadTransportException {
		System.out.println(
			"[Meniu terminal]\n" +
			"Actiuni valabile:"
		);
		System.out.println(
			"  balance - pentru verificarea soldului\n" +
			"  debit <suma> - pentru a debita cu suma dorita\n" +
			"  credit <suma> - pentru a credita cu suma dorita\n" +
			"  exit - pentru a parasi meniul\n"
		);
		
		Scanner in = new Scanner(System.in);
		
		// preiau input pana la comanda "exit"
		while (true) {
			System.out.print("> ");
			
			String action = in.nextLine().toLowerCase();
			
			if (action.compareTo("exit") == 0) {
				System.out.println("Meniul a fost inchis.");
				break;
			}
			
			if (action.compareTo("balance") == 0) {
				Action(action, (byte) 0);
				continue;
			}
			
			if (action.startsWith("debit") || action.startsWith("credit")) {
				String[] tokens = action.split(" ");

				if (tokens.length == 2) {
					if (!tokens[1].matches("[0-9]+")) {
						System.out.println("Valoare eronata.");
						continue;
					}
						
					int amount = Integer.parseInt(tokens[1], 10);
					if (amount > 127) {
						System.out.println("Tranzactia depaseste maximul de 127.");
						continue;
					}
					
					Action(tokens[0], amount);
					
					continue;
				}
			}
			
			System.out.println("Comanda eronata.");
		}
		
		in.close();
	}
	
	private void Action(String action, int amount) throws IOException, CadTransportException {
		if (action.compareTo("balance") == 0) {
			String command = "0x80 0x50 0x00 0x00 0x00 0x02;";
			Process(command);
			return;
		}
		
		if (action.compareTo("credit") == 0) {
			String command = "0x80 0x30 0x00 0x00 0x01 ? 0x7F;"; // "?" actioneaza ca placeholder
			command = command.replace("?", Integer.toHexString(amount));
			Process(command);
			return;
		}
		
		if (action.compareTo("debit") == 0) {
			if (!Verify(amount)) { // initializez procedura CVM, anulez operatiunea de debit in caz de esec
				System.out.println("Nu s-a putut efectua operatiunea de debit. Verificarea identitatii a esuat!");
				return;
			}
			
			// procedura CVM a avut succes, operatiunea de debit se proceseaza
			String command = "0x80 0x40 0x00 0x00 0x01 ? 0x7F;"; // "?" actioneaza ca placeholder
			command = command.replace("?", Integer.toHexString(amount)); 
			Process(command);
			return;
		}
	}
	
	private void GetCVM() throws IOException, CadTransportException {
		String command = "0x80 0x60 0x00 0x00 0x00 0x1e;"; // 0x1e=30, ne asteptam la 2 bytes (v1, v2) si maximum 14 perechi de bytes (cvm, cvr) 
		Apdu apdu = Process(command);
		
		// configurez lista cvm cu datele primite de la card
		if (apdu.getLe() >= 2) {
			V1 = apdu.dataOut[0];
			V2 = apdu.dataOut[1];
			
			final int n = (apdu.getLe()-2) / 2;
			CVM = new byte[n][2];
			
			for (int i = 0; i < n; i++) {
				CVM[i][0] = apdu.dataOut[i*2 + 2]; // codul cvm
				CVM[i][1] = apdu.dataOut[i*2 + 3]; // codul conditiei cvm
			}
		}
		
		Log("");
	}
	
	private boolean Verify(int amount) throws IOException, CadTransportException {
		// procesez in ordine fiecare CVM din lista obtinuta de pe card
		for (int i = 0; i < CVM.length; i++) {
			byte cvm = CVM[i][0];
			byte cvr = CVM[i][1];

			if (Search("cvr", cvr)) { // codul de conditie cvm este acceptat de terminal
				if (cvr == 0x6 && amount < V1) { // conditia este satisfacuta: tranzactie < 50
					if (Search("cvm", cvm) && cvm == 0b0101_1111) { // codul cvm este acceptat de terminal: nu necesita verificare
						return true;
					}
					
					// codul cvm nu este acceptat de terminal sau verificarea a esuat analizez b7
					if (((cvm >> 7) & 1) == 0) { // b7=0, procedura de verificare esueaza
						return false;
					}
					
					continue; // b7=1, procesarea listei cvm continua
				}
				
				if (cvr == 0x9 && amount > V2) { // necesita verificare pin in plaintext pt tranzactii >= 50
					if (Search("cvm", cvm) && cvm == 0b0000_0001) { // codul cvm este acceptat de terminal: verificare pin in plaintext
						Scanner in = new Scanner(System.in);
						
						// preia si verifica PIN-ul trecut de cardholder in consola
						while (true) {
							System.out.print("PIN: ");	
							
							String pin = in.nextLine();
							
							if (pin.compareTo("exit") == 0) {
								return false;
							}
							
							if (!pin.matches("[0-9]+")) {
								System.out.println("Valoare eronata.");
								continue;
							}
							
							int n = pin.length();
							String command = "0x80 0x20 0x00 0x00 " + n + " ";
							
							// completez comanda de verificare pin cu pin-ul trecut de cardholder
							for (int k = 0; k < n; k++) {
								command += pin.charAt(k) + " ";
							}
							
							command += "0x7F";
							
							Apdu apdu = Process(command);
							byte[] sw1sw2 = apdu.getSw1Sw2();
							
							// verific rezultatul comenzii
							if (sw1sw2[0] == (byte) 0x90 && sw1sw2[1] == 0x00) { // pin-ul este corect
								return true; // procedura de verificare a avut succes
							}
							
							System.out.println("PIN incorect!");
						}
					}
					
					// codul cvm nu este acceptat de terminal sau verificarea a esuat analizez b7
					if (((cvm >> 7) & 1) == 0) { // b7=0, procedura de verificare esueaza
						return false;
					}
					
					continue; // b7=1, procesarea listei cvm continua
				}
			}
		}
		
		return false;
	}
	
	private boolean Search(String where, byte value) {
		if (where.compareTo("cvm") == 0) {
			// cauta codul cvm in lista de cvm-uri acceptate de terminal
			for (int i = 0; i < supportedCVM.length; i++) {
				if (value == supportedCVM[i]) {
					return true;
				}
			}
			
			return false;
		}
		
		if (where.compareTo("cvr") == 0) {
			// cauta codul conditiei cvm in lista de coduri de conditie cvm acceptate de terminal
			for (int i = 0; i < supportedCVR.length; i++) {
				if (value == supportedCVR[i]) {
					return true;
				}
			}
			
			return false;
		}
		
		return false;
	}
	
	private void Request(Apdu apdu) {
		System.out.println("<trimis> " + apdu);
	}
	
	private void Response(Apdu apdu) {
		System.out.println("<primit> " + apdu);
		
		byte[] sw1sw2 = apdu.getSw1Sw2();
		String result = "";
		
		if (sw1sw2[0] == (byte) 0x90 && sw1sw2[1] == 0x00) {
			result = " a fost efectuata cu succes!";
		}
		else {
			result = " a esuat.";
		}
		
		byte ins = apdu.getCommand()[1];
		String command = "";
		String details = "";
		
		switch (ins) {
			case 0x20: // verify
				command = "verificare PIN";
				break;
			case 0x30: // credit
				command = "creditare";
				break;
			case 0x40: // debit
				command = "debitare";
				break;
			case 0x50: // get balance
				command = "verificare sold";
				details = " Sold curent: " + apdu.getDataOut()[1];
				break;
			case 0x60: // get cvm
				command = "obtinere CVM";
				break;
		}
		
		System.out.println("Operatiunea de " + command + result + details);
	}
	
	private void Log(String log) {
		System.out.println(log);
	}
}