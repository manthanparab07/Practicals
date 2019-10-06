
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.Scanner ;

public class DNS_Lookup {
	public static void main(String[] args) {
	
		Scanner in = new Scanner( System.in );
		String websiteName ;
		try {
			InetAddress inetAddress = InetAddress.getLocalHost();
			System.out.print(" Enter Website Name : ");
			websiteName = in.nextLine() ;
			inetAddress = InetAddress.getByName(websiteName);
			displayStuff(websiteName, inetAddress);
			System.out.println("--------------------------");
			InetAddress[] inetAddressArray = InetAddress.getAllByName(websiteName);
			for (int i = 0; i < inetAddressArray.length; i++) {
				displayStuff( websiteName +" #" + (i + 1), inetAddressArray[i]);
			}
		} catch (UnknownHostException e) {
			e.printStackTrace();
		}
	}

	public static void displayStuff(String whichHost, InetAddress inetAddress) {
		System.out.println("--------------------------");
		System.out.println("Which Host:" + whichHost);
		System.out.println("Canonical Host Name:" + inetAddress.getCanonicalHostName());
		System.out.println("Host Name:" + inetAddress.getHostName());
		System.out.println("Host Address:" + inetAddress.getHostAddress());
	}
}

