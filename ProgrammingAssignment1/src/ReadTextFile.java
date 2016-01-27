import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

/**
 * Created by lanceli on 2016-01-26.
 */
public class ReadTextFile {
    private String dirPath;
    private String filePath;
    ArrayList<Integer> lineArrayList = new ArrayList<Integer>();


    public ReadTextFile(String dirPath){
        this.dirPath = dirPath;
        this.filePath = this.dirPath+"/input.txt";
    }

    public void PopulateArray(){
        BufferedReader br = null;
        try {
            br = new BufferedReader(new FileReader(filePath));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        try {
            StringBuilder sb = new StringBuilder();
            String line = br.readLine();

            while (line != null) {
                lineArrayList.add(Integer.parseInt(line));
                line = br.readLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public ArrayList<Integer> getLineArrayList(){
        PopulateArray();
        return this.lineArrayList;
    }


}
