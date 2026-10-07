// Students:                                  IDs:                       Filters:
// 1- Youssef Ehab Ahmed            -         20242428         -         grayScale / flipImage / mergeImages / SunlightFilter
// 2- Ibrahim Mohamed Hosny         -         20250006         -         blackAndWhite / rotateImage / detectEdges / oilPainting
// 3- Seif Khaled Ragab             -         20251205         -         invertImage / darkenAndLighten / cropImage / purpleEffect
// 4- Youssef Saied Helmy           -         20251496         -         addFrame / imageResize / blurImage / infraredFilter


غخع

#include <algorithm>
#include <stack>
#include <iostream>
#include <fstream> 
#include <string>
#include "Image_Class.h"

using namespace std;






// ----------------------- Filters Functions. ----------------------------------

void sunlightFilter(Image &img)
{
    for (int i = 0; i < img.width; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                if (k == 0)
                {
                    int newValue = (img(i,j,k)* 1.25) + 15;
                    newValue = newValue > 255? 255: newValue;
                    img(i,j,k) = newValue;
                }
                else if (k==1)
                {

                    int newValue = (img(i,j,k)* 1.05); 
                    newValue = newValue > 255? 255: newValue;
                    img(i,j,k) = newValue;
                }
                else{
                    int newValue = (img(i,j,k)* 0.9);
                    newValue = newValue > 255? 255: newValue;
                    img(i,j,k) = newValue;
                }
            }
        }
    }
}

void mergeImages(Image &img1, Image img2)
{
    try
    {
        int width = min(img1.width, img2.width);
        int height = min(img1.height, img2.height);
        Image mergeImages(width, height);
        {
            for (int w = 0; w < width; w++)
            {
                for (int h = 0; h < height; h++)
                {
                    int red1 = img1.getPixel(w, h, 0);
                    int red2 = img2.getPixel(w, h, 0);

                    int green1 = img1.getPixel(w, h, 1);
                    int green2 = img2.getPixel(w, h, 1);

                    int blue1 = img1.getPixel(w, h, 2);
                    int blue2 = img2.getPixel(w, h, 2);

                    int newRed = (int)(red1 + red2) / 2;
                    int newGreen = (int)(green1 + green2) / 2;
                    int newBlue = (int)(blue1 + blue2) / 2;

                    mergeImages.setPixel(w, h, 0, newRed);
                    mergeImages.setPixel(w, h, 1, newGreen);
                    mergeImages.setPixel(w, h, 2, newBlue);
                }
            }
        }
        img1 = mergeImages;
    }
    catch (const exception &y)
    {
        cerr << "ERROR!!!" << y.what();
    }
}


void grayscale(Image &image)
{
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int avg = 0;

            for (int k = 0; k < 3; ++k)
            {
                avg += image(i, j, k);
            }

            avg /= 3;


            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }
}




void flipImage(Image &image)
{
    short choice;

    cout << "Press 1 for vertical flip\n";
    cout << "Press 2 for horizontal flip\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        for(int i = 0; i < image.width/2;i++){
            for(int j = 0; j <image.height;j++){
                for(int k = 0; k <3; k++){
                    unsigned char temp = image(i,j,k);
                    image(i,j,k) = image(image.width-i-1,j,k);
                    image(image.width-i-1,j,k) = temp;
                }
            }
        }
    };
    break;

    case 2:
    {
        for (int j = 0; j < image.height / 2; j++)
        {
            for (int i = 0; i < image.width; i++)
            {
                for (int k = 0; k < 3; k++)
                {
                    unsigned char temp = image(i, j, k);
                    image(i,j,k) = image(i,image.height-j-1,k);
                    image(i,image.height-1-j,k) = temp;
                }
            }
        }
    }

    }
}




void blackAndWhite(Image& image) {
    for(int y = 0; y < image.height; ++y) {
        for(int x = 0; x < image.width; ++x) {
            int r = image.getPixel(x, y, 0);
            int g = image.getPixel(x, y, 1);
            int b = image.getPixel(x, y, 2);

            int avg = (r + g + b) / 3;
            if(avg < 128) {
                image.setPixel(x, y, 0, 0);
                image.setPixel(x, y , 1, 0);
                image.setPixel(x, y, 2, 0);
            } else {
                image.setPixel(x, y, 0, 255);
                image.setPixel(x, y , 1, 255);
                image.setPixel(x, y, 2, 255);
            }
        }
    }
}




void rotateImage(Image& image, int angle) {
    int height = image.height;
    int width = image.width;
    int newWidth = width, newHeight = height;

    if(angle == 0) return;
    if(angle == 90 || angle == 270) {newWidth = height; newHeight = width;}
    else if(angle == 180) {newWidth= width; newHeight = height;}
    else return;

    Image temp(newWidth, newHeight);

    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) {
            int newX, newY;
            if(angle == 90 ) {newX = height - 1 - y; newY = x;}
            if(angle == 180) {newX = width - 1 - x; newY = height - 1 - y;}
            if(angle == 270) {newX = y; newY = width - 1 - x;}

            int r = image.getPixel(x, y, 0);
            int g = image.getPixel(x, y, 1);
            int b = image.getPixel(x, y, 2);

            temp.setPixel(newX, newY, 0, r);
            temp.setPixel(newX, newY, 1, g);
            temp.setPixel(newX, newY, 2, b);
        }
    }

    image = temp;
}





void invertImage(Image& image){
    for(int y=0;y<image.height;y++){
        for(int x=0;x<image.width;x++){
            int r=255-image(x,y,0);
            int g=255-image(x,y,1);
            int b=255-image(x,y,2);
            image(x,y,0)=r;
            image(x,y,1)=g;
            image(x,y,2)=b;
            }
    }
}




void darkAndlightImage(Image& image, int percentage, int choice)
{
    for (int y = 0; y < image.height; y++)
    {
        for (int x = 0; x < image.width; x++)
        {
            int r = image(x, y, 0);
            int g = image(x, y, 1);
            int b = image(x, y, 2);

            if (choice == 1)
            {
                r = r + (255 - r) * percentage / 100;
                g = g + (255 - g) * percentage / 100;
                b = b + (255 - b) * percentage / 100;
            }
            else if (choice == 2)
            {
                r = r - r * percentage / 100;
                g = g - g * percentage / 100;
                b = b - b * percentage / 100;
            }

            image(x, y, 0) = r;
            image(x, y, 1) = g;
            image(x, y, 2) = b;
        }
    }
}



void resizeImage(Image& image, int new_width, int new_height)
{
    Image result(new_width, new_height);

    for (int y = 0; y < new_height; y++)
    {
        for (int x = 0; x < new_width; x++)
        {
            int x_original = x * image.width / new_width;
            int y_original = y * image.height / new_height;

            result(x, y, 0) = image(x_original, y_original, 0);
            result(x, y, 1) = image(x_original, y_original, 1);
            result(x, y, 2) = image(x_original, y_original, 2);
        }
    }

    image = result;
}



void tvFilter(Image& image){
for(int y=0;y<image.height;y++){
    for(int x=0;x<image.width;x++){
        if(y%2==0){
            int R=image(x,y,0)*1.1;
            if(R > 255){
                R = 255;
            }
            int G=image(x,y,1)*1.2;
            if(G > 255){
                G = 255;
            }
        int B=image(x,y,2) * 0.7;
        image(x,y,0)=R;
        image(x,y,1)=G;
        image(x,y,2)=B;
                  }
        else{
            int R=(image(x,y,0)*1.1) / 1.5;
            if(R > 255){
            R = 255;
            }
            int G=(image(x,y,1)*1.2) / 1.5;
            if(G > 255){
            G = 255;
            }
            int B=(image(x,y,2)*0.7) / 1.5;
            image(x,y,0)=R;
            image(x,y,1)=G;
            image(x,y,2)=B;

        }
}
}
}











void detectEdges(Image& image) {
    int height = image.height, width = image.width;
    Image temp(width, height);
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            int red = image.getPixel(x, y, 0), green = image.getPixel(x, y, 1), blue = image.getPixel(x, y, 2);
            int nextXRed   = x < width - 1  ? image.getPixel(x + 1, y, 0) : image.getPixel(x - 1, y, 0);
            int nextXGreen = x < width - 1  ? image.getPixel(x + 1, y, 1) : image.getPixel(x - 1, y, 1);
            int nextXBlue  = x < width - 1  ? image.getPixel(x + 1, y, 2) : image.getPixel(x - 1, y, 2);
            int nextYRed   = y < height - 1 ? image.getPixel(x, y + 1, 0) : image.getPixel(x, y - 1, 0);
            int nextYGreen = y < height - 1 ? image.getPixel(x, y + 1, 1) : image.getPixel(x, y - 1, 1);
            int nextYBlue  = y < height - 1 ? image.getPixel(x, y + 1, 2) : image.getPixel(x, y - 1, 2);

            int currentAvg = (red + green + blue) / 3;
            int nextXAvg   = (nextXRed + nextXGreen + nextXBlue) / 3;
            int nextYAvg   = (nextYRed + nextYGreen + nextYBlue) / 3;

            int val = 255;
            if(abs(currentAvg - nextXAvg) > 75 || abs(currentAvg - nextYAvg) > 75) val = 0;

            temp.setPixel(x, y, 0, val);
            temp.setPixel(x, y, 1, val);
            temp.setPixel(x, y, 2, val);
        }
    }
    image = temp;
}



void oilPainting(Image& image) {
    int height = image.height, width = image.width;
    Image temp(width, height);

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            int intensity, levels = 30, bucket, radius = 2;
            int count[256] = {0}, sumR[256] = {0}, sumG[256] = {0}, sumB[256] = {0};

            for(int dy = -radius; dy <= radius; dy++) {
                for (int dx = -radius; dx <= radius; dx++) {
                    int nx = min(max(x + dx, 0), width - 1);
                    int ny = min(max(y + dy, 0), height - 1);
                    int r = image.getPixel(nx, ny, 0);
                    int g = image.getPixel(nx, ny, 1);
                    int b = image.getPixel(nx, ny, 2);
                    intensity = (r + g + b) / 3;
                    bucket = intensity * (levels - 1) / 255;
                    count[bucket]++  ;
                    sumR[bucket] += r;
                    sumG[bucket] += g;
                    sumB[bucket] += b;
                }
            }
            int best = 0;
            for(int i = 0; i < levels; i++) { if(count[i] > count[best]) best = i; }
            temp.setPixel(x, y, 0, sumR[best]/count[best]);
            temp.setPixel(x, y, 1, sumG[best]/count[best]);
            temp.setPixel(x, y, 2, sumB[best]/count[best]);
        }
    }
    image = temp;
}


void cropImage(Image& image, int x, int y, int width2, int height2){
    try{

        Image img(width2,height2);
        for(int w= 0; w < width2; w++){
            for(int h=0; h< height2; h++){
                int red =image.getPixel(x+w,y+h,0);
                int green =image.getPixel(x+w,y+h,1);
                int blue =image.getPixel(x+w,y+h,2);

                img.setPixel(w,h,0,red);
                img.setPixel(w,h,1,green);
                img.setPixel(w,h,2,blue);
            }

        }
        image = img;
    }
    catch(const exception& y){
        cerr<<"ERROR!!!"<<y.what();
    }
}





void purpleFilter(Image& image){
    try{
        for(int w =0 ; w< image.width ; w++){
            for(int h = 0 ; h< image.height ; h++){
                int red= image.getPixel(w,h,0);
                int green = image.getPixel(w,h,1);
                int blue= image.getPixel(w,h,2);
                int NewRed = min(255, (int) (red*1.3));
                int NewGreen = (int) (green*.5);
                int NewBlue = min(255,(int) (blue*1.3));
                image.setPixel(w,h,0,NewRed);
                image.setPixel(w,h,1,NewGreen);
                image.setPixel(w,h,2,NewBlue);
            }
        }
        image = image;
    }
    catch(const exception& y){
        cerr<<"ERROR"<<y.what();
    }
}


void addFrame(Image& image, int frame, int type){
    try{
        int newWidth = image.width + (2*frame);
        int newHeight = image.height + (2*frame);
        Image border_img(newWidth,newHeight);

        if(type == 1){
            for(int w =0;w<image.width;w++){
                for(int h = 0;h<image.height;h++){
                    int red = image.getPixel(w,h,0);
                    int green = image.getPixel(w,h,1);
                    int blue = image.getPixel(w,h,2);

                    border_img.setPixel(w+frame,h+frame,0,red);
                    border_img.setPixel(w+frame,h+frame,1,green);
                    border_img.setPixel(w+frame,h+frame,2,blue);
                }
            }
        }
        else{
            int thin = max(1, frame / 10);
            int outer = max(0, frame - 3 * thin);

            for(int x = 0; x < newWidth; x++){
                for(int y = 0; y < newHeight; y++){
                    bool insidePhoto = x >= frame && x < frame + image.width &&
                                       y >= frame && y < frame + image.height;

                    int r, g, b;

                    if(insidePhoto){
                        r = image.getPixel(x - frame, y - frame, 0);
                        g = image.getPixel(x - frame, y - frame, 1);
                        b = image.getPixel(x - frame, y - frame, 2);
                    }
                    else{
                        int d = min(min(x, y), min(newWidth - 1 - x, newHeight - 1 - y));
                        int color;

                        if(d < outer) color = 0;
                        else if(d < outer + thin) color = 255;
                        else if(d < outer + 2 * thin) color = 0;
                        else color = 255;

                        r = color;
                        g = color;
                        b = color;
                    }

                    border_img.setPixel(x, y, 0, r);
                    border_img.setPixel(x, y, 1, g);
                    border_img.setPixel(x, y, 2, b);
                }
            }
        }

        image = border_img;
    }
    catch(const exception& y){
        cerr<<"ERROR!!"<<y.what();
    }
}




void blurImage(Image& image) {
    try {
        Image blured(image.width, image.height);

        for (int w = 0; w < image.width; w++) {
            for (int h = 0; h < image.height; h++) {

                int sumRed = 0, sumGreen = 0, sumBlue = 0;
                int count = 0;

                for (int dw = -7; dw <= 7; dw++) {
                    for (int dh = -7; dh <= 7; dh++) {

                        int besideW = w + dw;
                        int besideH = h + dh;

                        if (besideW >= 0 && besideW < image.width &&
                            besideH >= 0 && besideH < image.height) {

                            sumRed += image.getPixel(besideW, besideH, 0);
                            sumGreen += image.getPixel(besideW, besideH, 1);
                            sumBlue += image.getPixel(besideW, besideH, 2);

                            count++;
                        }
                    }
                }


                blured.setPixel(w, h, 0, sumRed / count);
                blured.setPixel(w, h, 1, sumGreen / count);
                blured.setPixel(w, h, 2, sumBlue / count);
            }
        }
            image = blured;
    }

    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}


void infraredFilter(Image& original){
    try{

        for(int w =0; w<original.width; w++){
            for(int h=0; h<original.height; h++){

                    int red = original.getPixel(w,h,0);
                    int green = original.getPixel(w,h,1);
                    int blue = original.getPixel(w,h,2);
                    int newRed=255;
                    int newGreen= 255-green;
                    int newBlue = 255-blue;
                    original.setPixel(w,h,0,newRed);
                    original.setPixel(w,h,1,newGreen);
                    original.setPixel(w,h,2,newBlue);
                }
                }
            }

        catch(exception& e){
    cerr<<"Error: "<<e.what()<<endl;
        }
    }



// ---------------------------------- Program Logic. ---------------------------------------



stack<Image> versions;
string filename;
bool isSaved = true;
Image image;


void saveImage() {
    int choice;

    cout << "Press 0 to exit save menu: \n";
    cout << "Press 1 to save in the same file: \n";
    cout << "Press 2 to save in a new file: \n";

    cin >> choice;

    if(choice == 1 || choice == 2) isSaved = true;
    if(choice == 0) {
        cout << "Exiting save menu";
    }
    else if(choice == 1) image.saveImage(filename);
    else if(choice == 2) {
        string newFile;
        cout << "Enter new file name: \n";
        cin >> newFile;

        image.saveImage(newFile);
    }
}


int main() {

    while(true) {

        cout << "============================================\n";
        cout << "       IMAGE PROCESSING PROGRAM\n";
        cout << "============================================\n";
        cout << "Press 0 to exit program: \n";
        cout << "Press 1 to load an image: \n";
        cout << "Press 2 to apply filters: \n";
        cout << "Press 3 to undo changes: \n";
        cout << "Press 4 to save changes:\n";

        int input;
        cin >> input;

        if (input == 0) {
            cout << "Exiting program. \n";
            return 0;
        }

        else if (input == 1) {
            if(!isSaved) {
                cout << "There are some unsaved changes.\n";
                cout << "Press 0 to cancel\n";
                cout << "Press 1 to discard changes\n";
                cout << "Press 2 to save changes\n";
                int savingChoice;
                cin >> savingChoice;

                if (savingChoice == 0) {continue;}
                else if (savingChoice == 1) {}
                else if (savingChoice == 2) saveImage();
        }
            cout << "Enter image name: \n";
            cin >> filename;
            Image loadedImage(filename);
            image = loadedImage;
            isSaved = true;
            cout << "Image loaded successfully. \n";
        }

        else if (input == 2) {
            if(filename.empty()) {
                cout << "Please load an image first!\n";
                continue;
            }

            cout << "0. Exit filter menu\n";
            cout << "1. Grayscale\n";
            cout << "2. Black and White\n";
            cout << "3. Invert Image\n";
            cout << "4. Add Frame\n";
            cout << "5. Flip Image\n";
            cout << "6. Rotate Image\n";
            cout << "7. Darken or Lighten Image\n";
            cout << "8. Resize Image\n";
            cout << "9. Merge Images\n";
            cout << "10. Detect Edges\n";
            cout << "11. Crop Image\n";
            cout << "12. Blur Image\n";
            cout << "13. Sunlight Filter\n";
            cout << "14. TV Filter\n";
            cout << "15. Purple Filter\n";
            cout << "16. Infrared Filter\n";
            cout << "17. Skew Image\n";
            cout << "18. Oil Painting\n";

            int filterChoice;
            cin >> filterChoice;

            if(filterChoice > 0 && filterChoice < 20) {
                versions.push(image);
                isSaved = false;
            }

            switch (filterChoice) {

            case 0:
                cout << "Exiting filter menu.\n";
                continue;

            case 1:
                grayscale(image);
                cout << "Grayscale filter applied successfully.\n";
                break;

            case 2:
                blackAndWhite(image);
                cout << "Black and White filter applied successfully.\n";
                break;

            case 3:
                invertImage(image);
                cout << "Invert filter applied successfully.\n";
                break;

            case 4:
                int frame;
                cout<<"Enter the frame size: ";
                cin>>frame;
                int type;
                cout<<"Enter the frame type: ";
                cin>>type;
                 addFrame(image,frame,type);
                cout << "Frame added successfully.\n";
                break;

            case 5:
                flipImage(image);
                cout << "Flip filter applied successfully.\n";
                break;

            case 6: {
                int angle;

                cout << "Enter rotation angle (90, 180, or 270): ";
                cin >> angle;

                rotateImage(image, angle);
                cout << "Rotate filter applied successfully.\n";
                break;
            }

             case 7:
                            {
                int percentage;
                int choice;

                cout << "1. Lighten image" << endl;
                cout << "2. Darken image" << endl;
                cout << "Choose: ";
                cin >> choice;

                cout << "Enter percentage (0 - 100): ";
                cin >> percentage;

                if (percentage < 0 || percentage > 100)
                {
                    cout << "Invalid percentage!" << endl;
                }
                else
                {
                    if (choice == 1)
                    {
                        darkAndlightImage(image, percentage, 1);
                    }
                    else if (choice == 2)
                    {
                        darkAndlightImage(image, percentage, 2);
                    }
                }
                break;
                            }

             case 8: {

                    int newWidth, newHeight;

                cout << "Enter new width: ";
                cin >> newWidth;

                cout << "Enter new height: ";
                cin >> newHeight;
                resizeImage(image, newWidth, newHeight);
                cout << "Resize filter applied successfully.\n";
                break;
                }

            case 9: {
                string filename;

                cout << "Enter the filename of the second image: ";
                cin >> filename;

                Image secondImage(filename);

                mergeImages(image, secondImage);
                cout << "Merge filter applied successfully.\n";
                break;
            }

            case 10:
                detectEdges(image);
                cout << "Edge detection filter applied successfully.\n";
                break;

            case 11: {
                int startX, startY, width, height;

                cout << "Enter starting X: ";
                cin >> startX;

                cout << "Enter starting Y: ";
                cin >> startY;

                cout << "Enter crop width: ";
                cin >> width;

                cout << "Enter crop height: ";
                cin >> height;

                cropImage(image, startX, startY, width, height);
                cout << "Crop filter applied successfully.\n";
                break;
            }

            case 12:
                blurImage(image);
                cout << "Blur filter applied successfully.\n";
                break;

            case 13:
                sunlightFilter(image);
                cout << "Sunlight filter applied successfully.\n";
                break;

            case 14:
                tvFilter(image);
                cout << "TV filter applied successfully.\n";
                break;

            case 15:
                purpleFilter(image);
                cout << "Purple filter applied successfully.\n";
                break;

            case 16:
                infraredFilter(image);
                cout << "Infrared filter applied successfully.\n";
                break;

            // case 17:
            //     skewImage(image);
            //     cout << "Skew filter applied successfully.\n";
            //     break;

            case 18:
                oilPainting(image);
                cout << "Oil Painting filter applied successfully.\n";
                break;

            default:
                cout << "Invalid filter choice.\n";
                break;
        }
        }

        else if(input == 3) {
            if(filename.empty()) {
                cout << "Please load an image first!\n";
                continue;
            }
            if(versions.empty()) {
                cout << "Nothing to undo!\n";
                continue;
            }
            image = versions.top();
            versions.pop();
            isSaved = false;
        }

        else if(input == 4) {
            if(filename.empty()) {
                cout << "Please load an image first!\n";
                continue;
            }
            saveImage();
        }
    }
}
