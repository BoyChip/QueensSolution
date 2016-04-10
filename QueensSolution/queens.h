#ifndef QUEENS_H
#define QUEENS_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QLabel>
#include <QMessageBox>
#include <QMouseEvent>
#include <QIcon>
#include <QString>


#include "solution_queens.h"

#define MAX_INT 5000
#define MAX_COL 12
#define MAX_ROW 32767

namespace Ui {
class queens;
}

class queens : public QWidget
{
    Q_OBJECT

public:
    explicit queens(QWidget *parent = 0);
    ~queens();
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *event);
    void virtual mousePressEvent(QMouseEvent *evt);

    double timerId;
    double postition;


    void read_data();
    void clearn_data();
    void check_stop();
    void draw_chessboard(QPainter& painters);
    void draw_queen(QPainter& p);
    int mode;// biến thay đổi chế độ chơi của game.
    int mode2;// biến lưu giá trị của việc vẽ quân hậu lên bàn cờ (trong chế độ người chơi)
    int check;// kiểm tra giá trị dừng của game (trong chế độ người chowi0

    int mouse_x;// lấy giá trị x của click trái chuột
    int mouse_y;// lấy giá trị y của click trái chuột
    int mouse_x_local[MAX_INT];// lưu giá trị x của tất cả các click trái chuột để kiểm tra
    int mouse_y_local[MAX_INT];// lưu giá trị y của tất cả các click trái chuột để kiểm tra
    int total_mouse;// tổng số lần click trái chuột được chấp nhận
    int size_x;//
    int size_y;

    int N;// số lượng quân hậu
    int total_result;// tổng số lời giải được chấp nhận của N quân hậu
    int index;// vị trí hiện tại của lời giải

    int result[MAX_ROW][MAX_COL];
    int result_index[MAX_COL];

    FILE *fp;

private slots:
    void on_button_computer_clicked();

    void on_button_next_clicked();

    void on_button_previous_clicked();

    void on_button_player_clicked();

    void on_button_clear_clicked();

    void on_button_exit_clicked();

private:
    Ui::queens *ui;
};

#endif // QUEENS_H
