package com.epicgames.ue4;

import com.Juno.comet_dreams.OBBDownloaderService;
import com.Juno.comet_dreams.DownloaderActivity;


public class DownloadShim
{
	public static OBBDownloaderService DownloaderService;
	public static DownloaderActivity DownloadActivity;
	public static Class<DownloaderActivity> GetDownloaderType() { return DownloaderActivity.class; }
}

