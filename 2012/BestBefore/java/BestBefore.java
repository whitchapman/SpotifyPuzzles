import java.io.*;
import java.util.*;

class PossibleDate implements Comparable {
	private int month;
	private int day;
	private int year;

	public PossibleDate(int month, int day, int year) {
		this.month = month;
		this.day = day;
		if (year < 100) {
			this.year = 2000 + year;
		} else {
			this.year = year;
		}
	}

	public int compareTo(Object obj) {
		int result = Integer.compare(this.year, ((PossibleDate)obj).year);
		if (result == 0) {
			result = Integer.compare(this.month, ((PossibleDate)obj).month);
			if (result == 0) {
				return Integer.compare(this.day, ((PossibleDate)obj).day);
			}
		}
		return result;
	}

	public String toString() {
		return String.format("%04d-%02d-%02d", this.year, this.month, this.day);
	}

	public boolean isValid() {
		if ((year < 2000) || (year > 2999)) {
			return false;
		}

		if ((month < 1) || (month > 12)) {
			return false;
		}

		switch (month) {
			case 2:
				if (day == 29) {
					//check for leap year

					if (year % 4 != 0) {
						return false;
					}

					if ((year % 100 == 0) && (year % 400 != 0)) {
						return false;
					}

					return true;
				}

				return ((day > 0) && (day < 29));

			case 4:
			case 6:
			case 9:
			case 11:
				return ((day > 0) && (day < 31));

			default:
				return ((day > 0) && (day < 32));
		}
	}
}


public class BestBefore {

	private static void test_permutation(ArrayList<PossibleDate> al, int m, int d, int y) {
		PossibleDate pd = new PossibleDate(m, d, y);
		if (pd.isValid()) {
			al.add(pd);
		}
	}

	public static void main(String[] args) {
		try {

			Reader reader = new InputStreamReader(System.in);
			BufferedReader buffer = new BufferedReader(reader);
			String line = buffer.readLine();
			buffer.close();

			String[] arr = line.split("/", 3);

			int x1 = Integer.parseInt(arr[0]);
			int x2 = Integer.parseInt(arr[1]);
			int x3 = Integer.parseInt(arr[2]);
			

			ArrayList<PossibleDate> al = new ArrayList<PossibleDate>();
			test_permutation(al, x1, x2, x3);
			test_permutation(al, x1, x3, x2);
			test_permutation(al, x2, x1, x3);
			test_permutation(al, x2, x3, x1);
			test_permutation(al, x3, x1, x2);
			test_permutation(al, x3, x2, x1);

			if (al.size() > 0) {

				PossibleDate pd = al.get(0);
				if (al.size() > 1) {
					for (int i=1; i < al.size(); i++) {
						if (pd.compareTo(al.get(i)) > 0) {
							pd = al.get(i);
						}
					}
				}

				System.out.println(pd.toString());

			} else {

				System.out.println(line + " is illegal");

			}

		} catch (IOException exn) {
			System.err.print("Exception reading from stdin:  ");
			exn.printStackTrace();
		} catch (Exception exn) {
			System.err.print("Exception:  ");
			exn.printStackTrace();
		}
	}

}
