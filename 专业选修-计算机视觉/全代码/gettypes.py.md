# gettypes.py

```python
import cv2
import json

BASIC_PATH = 'E:/CVtask/test_clips/'
SAVE_PATH = 'E:/CVtask/test_clips_images/'
path = 'E:/CVtask/data_test.json'
# index = 0
fw1 = open("alltypes.txt", "w")
myset = set()
with open(path, 'r') as f:
    data = json.load(f)
# 提取每个clip
clips = data['clips']
for clip in clips:
    annotations = clip['annotations']
    clip_uid = clip['clip_uid']
    # cap = cv2.VideoCapture(BASIC_PATH + clip_uid + '.mp4')
	# 提取每个annotation的obj_title
    for annotation in annotations:
        # visual_crop = annotation['visual_crop']
        # cap.set(cv2.CAP_PROP_POS_FRAMES, visual_crop['frame_number'] * 6)
        # ret, img = cap.read()
        obj_title = str(annotation['object_title'])
		# 没有出现过这个物品则加入
        if obj_title not in myset:
            myset.add(obj_title)
            fw1.write(obj_title)
            fw1.write('\n')
        else:
            continue
```

‍
