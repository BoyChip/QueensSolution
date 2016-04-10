#include "queens.h"
#include "ui_queens.h"

queens::queens(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::queens)
{
    ui->setupUi(this);
}

queens::~queens()
{
    delete ui;
}

void queens::paintEvent(QPaintEvent *)
{
    QPainter painters(this);
    painters.setRenderHint(QPainter::Antialiasing);

    // neu mode bang 1 thi chuyen sang che do may choi ve ban co cung voi ket qua quan hau
    if (mode == 1)
    {
        // lay tung dong trong ma tran ket qua
        for (int i = index; i <= index; i++)
            for (int j = 0; j < N; j++)
            {
                result_index[j] = result[i][j];
            }
        //ve ban co
        draw_chessboard(painters);
        //ve ket qua quan hau len ban co
        QImage img;
        img.load(":/MyPic/queen.png");
        img = img.scaled(size_x, size_y);
        for (int x = 0; x < N; x++)
            painters.drawImage(result_index[x]*size_x, x*size_y, img);
    }

    // neu mode bang 2 thi chuyen qua che do nguoi choi chi ve ban co
    if (mode == 2)
    {
        // ve ban co
        draw_chessboard(painters);

        // ve vi tri hien tai khi click chuot trai cua quan hau len ban co
        if (mode2 != 0) draw_queen(painters);

        // tim cac quan hau trung nhau sau do xoa ra khoi danh sach
        for (int i = total_mouse; i > 0; i--)
        {
            for (int j = i-1; j >= 0; j-- )
            {
                if ((mouse_x_local[i] == mouse_x_local[j]) && (mouse_y_local[i] == mouse_y_local[j]))
                {
                    mouse_x_local[j] = -1;
                    mouse_y_local[j] = -1;
                }
            }
        }
        // kiem tra quan hau co bi trung voi quan hau truoc do hay khong neu trung voi bat ky quan hau co truoc
        // thi se xoa quan hau co truoc chi giu lai quan hau sau cung khong bi trung.
        for (int i = total_mouse; i > 0; i--)
            for (int j = i-1; j >= 0; j--){
                if ((mouse_x_local[i] != -1) && (mouse_x_local[i] == mouse_x_local[j]))
                {
                    mouse_x_local[j] = -1;
                }
                if ((mouse_y_local[i] != -1) &&(mouse_y_local[i] == mouse_y_local[j]))
                {
                    mouse_y_local[j] = -1;
                }
                if ((mouse_x_local[i] != -1) && ((mouse_x_local[i] + mouse_y_local[i]) == (mouse_x_local[j] + mouse_y_local[j])))
                {
                    mouse_x_local[j] = -1;
                    mouse_y_local[j] = -1;
                }
                if ((mouse_x_local[i] != -1) && (mouse_x_local[i] - mouse_y_local[i]) == (mouse_x_local[j] - mouse_y_local[j]))
                {
                    mouse_x_local[j] = -1;
                    mouse_y_local[j] = -1;
                }
            }
        fp = fopen("mouse_result.txt","w");
        check = 0;
        QImage img;
        img.load(":/MyPic/queen.png");
        img = img.scaled(size_x, size_y);
        for (int i = 0; i <= total_mouse; i++)
        {
            if ((mouse_x_local[i] != -1) && (mouse_y_local[i] != -1)){
                check++;
                painters.drawImage(mouse_x_local[i]*size_x, mouse_y_local[i]*size_y, img);
                fprintf(fp, "%d %d\n", mouse_x_local[i], mouse_y_local[i]);
            }
        }
        fclose(fp);
    }
}

void queens::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
}

void queens::mousePressEvent(QMouseEvent *evt)
{
    if (evt->button() == Qt::LeftButton)
    {
        if (check != N){
            if ((mouse_x <= size_x*(N)) && (mouse_y <= (size_y*N))){
                if (mode == 2){
                    total_mouse++;
                    mouse_x = evt->x();
                    mouse_y = evt->y();
                    mode2++;
                    repaint();
                }
            }
        }
        else {
            check_stop();
        }
    }
    //QMessageBox::information(this, "info", QString::number(evt->pos().x()) + " " + QString::number(evt->pos().y()));
}

//doc du lieu tu file gan vao mang result
void queens::read_data()
{
    index = 0;
    fp = fopen("total_result.txt","r");
    fscanf(fp,"%d", &total_result);
    fclose(fp);

    fp = fopen("result.txt","r");
    for (int i = 0; i < total_result; i++)
    {
        for (int j = 0; j < N; j++)
        {
            fscanf(fp,"%d", &result[i][j]);
        }
    }
    fclose(fp);
}

void queens::clearn_data()
{
    total_mouse = -1;
    mode2 = 0;
}

void queens::check_stop()
{
    QMessageBox::StandardButton reply;
    if (check == N) {
        QMessageBox::information(this, "Thông báo !", "Bạn đã chiến thắng !");
        reply = QMessageBox::information(this, "Thông báo !","Bạn có muốn chơi tiếp không!", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes){
            clearn_data();
            check = 0;
        }
        if (reply == QMessageBox::No)
        {
            QApplication::quit();
        }
    }
}

void queens::draw_chessboard(QPainter &painters)
{
    //ve ban co
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++){
            if ((x+y)%2 == 1){
                painters.setBrush(Qt::blue);
                painters.drawRect(y*size_x,x*size_y,size_x,size_y);
            }
            else{
                painters.setBrush(Qt::white);
                painters.drawRect(y*size_x,x*size_y,size_x,size_y);
            }
        }
}

void queens::draw_queen(QPainter &p)
{
    if ((mouse_x <= size_x*(N)) && (mouse_y <= (size_y*N))){
        // xac dinh vi tri cua quan hau hien tai bang bien mouse_x_local
        int i = 0;
        while (mouse_x >= size_x*i)
        {
            i++;
        }
        mouse_x_local[total_mouse] = i-1;

        int j = 0;
        while (mouse_y >= size_y*j)
        {
            j++;
        }
        mouse_y_local[total_mouse] = j-1;

        //ve quan hau len ban co
        QImage img;
        img.load(":/MyPic/queen.png");
        img = img.scaled(size_x, size_y);
        p.drawImage(mouse_x_local[total_mouse]*size_x, mouse_y_local[total_mouse]*size_y, img);
    }
    else
    {
        mouse_x_local[total_mouse] = -1;
        mouse_y_local[total_mouse] = -1;
    }
}

void queens::on_button_computer_clicked()
{
    N = ui->text_number_queens->text().toInt();

    if ((N < 0) || (N == 0) || (N == 2) || (N == 3) || (N > 12)){
        QMessageBox::information(this, "Error!", "Dữ liệu không phù hợp !");
        //exit(EXIT_FAILURE);
    }
    else{
        size_x = width()/(N+2);
        size_y = height()/(N);
        fp = fopen("number_queen.txt","w");
        fprintf(fp, "%d", N);
        fclose(fp);

        if (remove("result.txt") == 0){
        }

        solution_queens _queens;
        _queens.run();

        read_data();

        mode = 1;
        repaint();
    }
}

void queens::on_button_next_clicked()
{
    if (mode == 1){
        if (index < total_result-1){
            index++;
            repaint();
        }
        else
            QMessageBox::information(this, "Thông báo !","Cuối danh sách !");
    }
}

void queens::on_button_previous_clicked()
{
    if (mode == 1){
        if (index > 0){
            index--;
            repaint();
        }
        else
            QMessageBox::information(this,"Thông báo !","Đầu danh sách !");
    }
}

void queens::on_button_player_clicked()
{
    N = ui->text_number_queens->text().toInt();

    if ( (N < 0) || (N == 0) || (N == 2) || (N == 3) || (N > 12)){
        QMessageBox::information(this, "Error!", "Dữ liệu không phù hợp !");
        //exit(EXIT_FAILURE);
    }
    else{
        size_x = width()/(N+2);
        size_y = height()/(N);
        fp = fopen("number_queen.txt","w");
        fprintf(fp, "%d", N);
        fclose(fp);

        if (remove("result.txt") == 0){

        }

        if (remove("mouse_result.txt") == 0){

        }

        mode = 2;
        clearn_data();
        repaint();
    }

}

void queens::on_button_clear_clicked()
{
    if (mode == 2){
        clearn_data();
        repaint();
    }
}

void queens::on_button_exit_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::information(this, "Thông báo !","Bạn có muốn chơi tiếp không!", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes){
    }
    if (reply == QMessageBox::No)
    {
        QApplication::quit();
    }
}
