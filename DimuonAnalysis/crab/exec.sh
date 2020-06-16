echo "================= CMSRUN starting ===================="
tar xvzf Rochester.tar.gz
cmsRun -j FrameworkJobReport.xml -p PSet.py
echo "================= CMSRUN finished ===================="
