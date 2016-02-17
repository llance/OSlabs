/**
 * Created by lanceli on 2016-01-26.
 */
public class QuickSort implements Runnable {
    private int[] anArray;
    private int low;
    private int high;

    public QuickSort(int[] anArray, int low, int high){
        this.anArray = anArray;
        this.low = low;
        this.high = high;
    }

    private void quickSort(int[] arr, int low, int high) {
        System.out.println("arr.length : " + arr.length + " int low is : " + low + " int high is : " + high);
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
        for (int x = 0; i < arr.length-1; x++) {
            System.out.println("array is " + arr[x]);
        }


        // recursively sort two sub parts
        //System.out.println("low is : " + low + " and j is : " + j);

        if (low < j) {
            QuickSort myQuickSort = new QuickSort(arr, 0, j-1);
            Thread lowQsThread = new Thread();
            lowQsThread.start();
            myQuickSort.getSortedArray();
            try {
                System.out.println("waiting for thread to join");
                lowQsThread.join();

            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        //System.out.println("high is : " + high + " and i is : " + i);

        if (high > i){
            QuickSort myQuickSort = new QuickSort(arr, i, arr.length-1);
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

        quickSort(anArray, low, high);
    }

    public int[] getSortedArray(){
        return anArray;
    }
}
