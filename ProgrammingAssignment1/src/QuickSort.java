import java.util.ArrayList;
import java.util.Arrays;

/**
 * Created by lanceli on 2016-01-26.
 */
public class QuickSort implements Runnable {
    private int[] anArray;

    public QuickSort(int[] anArray){
        this.anArray = anArray;

    }




    private void quickSort(int[] arr, int low, int high) {
        if (arr == null || arr.length == 0)
            return;

        if (low >= high)
            return;

        // pick the pivot
        int middle = low + (high - low) / 2;

        int pivot = arr[middle];


        // make left < pivot and right > pivot
        int i = low, j = high;
        while (i <= j) {
            while (arr[i] < pivot) {
                i++;
            }

            while (arr[j] > pivot) {
                j--;
            }

            if (i <= j) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                i++;
                j--;
            }
        }

        // recursively sort two sub parts
        if (low < j) {
            QuickSort myQuickSort = new QuickSort(arr);
            Thread lowQsThread = new Thread(myQuickSort);
            lowQsThread.start();
            myQuickSort.getSortedArray();
            try {
                System.out.println("waiting for thread to join");
                lowQsThread.join();

            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        if (high > i){
            QuickSort myQuickSort = new QuickSort(arr);
            Thread highQsThread = new Thread(myQuickSort);
            highQsThread.start();

            try {
                System.out.println("waiting for thread to join");

                highQsThread.join();

            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            myQuickSort.getSortedArray();
        }
    }

    @Override
    public void run() {
        quickSort(anArray, 0, anArray.length - 1);
    }

    public int[] getSortedArray(){
        return anArray;
    }
}
