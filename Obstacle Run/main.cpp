#include "DxLib.h"
#include "GameManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(FALSE);
	SetWindowSizeExtendRate(1.5);

	if (DxLib_Init() == -1) { return -1; }

	SetDrawScreen(DX_SCREEN_BACK);

	//Z�o�b�t�@�ɑ΂���`���L���ɂ���
	SetUseZBufferFlag(TRUE);
	SetWriteZBufferFlag(TRUE);

	SetBackgroundColor(0, 100, 100);

	Game_manager gm = Game_manager();

	//�����L�[��������邩�A�E�B���h�E��������܂Ń��[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();  //��ʂ��N���A

		gm.update();
		gm.draw();

		ScreenFlip();      //����ʂ̓��e��\��ʂɔ��f
	}

	gm.finalize();

	DxLib_End();
	return 0;
}