import java.io.*;
import java.util.TreeSet;

public class ZipfsSong {

	public static void main(String[] args) {
		try {

			BufferedReader buffer = new BufferedReader(new InputStreamReader(System.in));

			String line = buffer.readLine();
			String[] arr = line.split(" ", 2);
			int num_songs = Integer.parseInt(arr[0]);
			int num_outputs = Integer.parseInt(arr[1]);

			TreeSet<Song> tree = new TreeSet<Song>();

			for (int i=1; i<=num_songs; i++) {
				line = buffer.readLine();
				arr = line.split(" ", 2);
				long num_plays = Long.parseLong(arr[0]);
				String title = arr[1];
				Song song = new Song(i, title, num_plays);
				tree.add(song);
			}

			buffer.close();

			for (int i=0; i<num_outputs; i++) {
				Song song = tree.pollFirst();
				System.out.println(song.get_title());
			}

		} catch (Exception exn) {
			System.err.print("Exception:  ");
			exn.printStackTrace();
		}
	}

}

class Song implements Comparable {
	private int track;
	private String title;
	private long num_plays;
	private long quality;

	public Song(int track, String title, long num_plays) {
		this.track = track;
		this.title = title;
		this.num_plays = num_plays;
		this.quality = track * num_plays;
	}

	public String get_title() {
		return this.title;
	}

	public int compareTo(Object obj) {
		if (this.quality < ((Song)obj).quality) {
			return 1;
		}

		if (this.quality > ((Song)obj).quality) {
			return -1;
		}

		//when qualities are equal, the lower track number comes first
		if (this.track < ((Song)obj).track) {
			return -1;
		}

		return 1;
	}
}
