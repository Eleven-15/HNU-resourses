# imgclip.py

```python
import cv2
import json

# 使用给出的json文件提取出识别的物体的图片，左移和右移一帧，所以一共3张图片，使训练素材丰富
BASIC_PATH = 'E:/CVtask/test_clips/'
SAVE_PATH = 'E:/CVtask/test_clips_images/'
path = 'E:/CVtask/data_test.json'
# index = 0
# fw1 = open("alltypes.txt", "w")
mydict = {}
# 打开json文件读取到data
with open(path, 'r') as f:
    data = json.load(f)
# 提取json中clips项
clips = data['clips']
# 接下来就是提取每一个clip，然后根据uid找到对应的视频然后截取图片
for clip in clips:
    annotations = clip['annotations']
    clip_uid = clip['clip_uid']
    cap = cv2.VideoCapture(BASIC_PATH + clip_uid + '.mp4')
    for annotation in annotations:
        visual_crop = annotation['visual_crop']
        obj_title = str(annotation['object_title'])
        for i in range(-1, 2):
            cap.set(cv2.CAP_PROP_POS_FRAMES, visual_crop['frame_number'] * 6 + i)
            ret, img = cap.read()
            if mydict.get(obj_title) is None:
                mydict[obj_title] = 1
                cv2.imwrite(SAVE_PATH + obj_title + '_' + str(mydict[obj_title]) + '.jpg', img)
            else:
                # fw1.write(str(index) + " " + annotation['object_title'])
                # fw1.write('\n')
                # index = index + 1
                # myset.add(obj_title)
                mydict[obj_title] += 1
                cv2.imwrite(SAVE_PATH + obj_title + '_' + str(mydict[obj_title]) + '.jpg', img)

```
