#include "DxLib.h"
#include "GameManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(FALSE);
	SetWindowSizeExtendRate(1.5);

	if (DxLib_Init() == -1) { return -1; }

	SetDrawScreen(DX_SCREEN_BACK);

	//Zバッファに対する描画を有効にする
	SetUseZBufferFlag(TRUE);
	SetWriteZBufferFlag(TRUE);

	SetBackgroundColor(0, 100, 100);

	Game_manager gm = Game_manager();

	//何かキーが押されるか、ウィンドウが閉じられるまでループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();  //画面をクリア

		gm.update();
		gm.draw();

		ScreenFlip();      //裏画面の内容を表画面に反映
	}

	gm.finalize();

	DxLib_End();
	return 0;
}