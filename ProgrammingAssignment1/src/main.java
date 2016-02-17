import java.util.ArrayList;

/**
 * Created by lanceli on 2016-01-26.
 */



public class main {
    public static void main(String[] args) {
        String currentDir = System.getProperty("user.dir");
        System.out.println("Working Directory = " + currentDir);
        ReadTextFile readTextFile = new ReadTextFile(currentDir);
        ArrayList<Integer> myAl = readTextFile.getLineArrayList();
        int[] myArray = convertIntegers(myAl);

        for (int i = 0; i < myAl.size(); i++) {
            System.out.println(myAl.get(i));
        }


        QuickSort myQuickSort = new QuickSort(myArray, 0, myArray.length-1);

        Thread qsThread = new Thread(myQuickSort);
        qsThread.start();

        int[] sortedArray =  myQuickSort.getSortedArray();

        try {
            System.out.println("waiting for thread to join");

            qsThread.join();

        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        for (int i=0; i<sortedArray.length ;i++){
            System.out.println("sortedArray[" + i + "] = " + sortedArray[i]);
        }

    }

    public static int[] convertIntegers(ArrayList<Integer> myArrayList)
    {
        int[] arr = new int[myArrayList.size()];
        for (int i=0; i < arr.length; i++)
        {
            arr[i] = myArrayList.get(i).intValue();
        }
        return arr;
    }
}

