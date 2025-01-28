# yolotxttransfer.py

```python
import cv2
import json

BASIC_PATH = 'E:/CVtask/test_clips/'
SAVE_PATH = 'E:/CVtask/test_clips_images/'
TXT_PATH = 'E:/CVtask/test_clips_yolotxt/'
path = 'E:/CVtask/data_test.json'
# index = 0
mydict = {}
types = {}
with open('E:/CVtask/classes_test.txt') as fr:
    contents = fr.read()
lines = contents.split("\n")
index = 0
for line in lines:
    types[line] = index
    index += 1
print(types)
with open(path, 'r') as f:
    data = json.load(f)
clips = data['clips']
for clip in clips:
    annotations = clip['annotations']
    clip_uid = clip['clip_uid']
    for annotation in annotations:
        visual_crop = annotation['visual_crop']
        obj_title = str(annotation['object_title'])
		# 根据visual_crop里面给出的数据，转换成yolo需要的标注集
        yolo_x, yolo_y, yolo_w, yolo_h = float(
            (visual_crop['x'] + visual_crop['width'] / 2) / visual_crop['original_width']), float(
            (visual_crop['y'] + visual_crop['height'] / 2) / visual_crop['original_height']), float(
            visual_crop['width'] / visual_crop['original_width']), float(
            visual_crop['height'] / visual_crop['original_height'])
		# 与截取图片的时候的命名保持一致，这样就非常方便，因为yolo是要图片和标注名字一样的
        for i in range(-1, 2):
            if mydict.get(obj_title) is None:
                mydict[obj_title] = 1
                with open(TXT_PATH + obj_title + '_' + str(mydict[obj_title]) + '.txt', 'a') as fw:
                    fw.write(
                        str(types[obj_title]) + ' ' + str(yolo_x) + ' ' + str(yolo_y) + ' ' + str(yolo_w) + ' ' + str(
                            yolo_h))
            else:
                mydict[obj_title] += 1
                with open(TXT_PATH + obj_title + '_' + str(mydict[obj_title]) + '.txt', 'a') as fw:
                    fw.write(
                        str(types[obj_title]) + ' ' + str(yolo_x) + ' ' + str(yolo_y) + ' ' + str(yolo_w) + ' ' + str(
                            yolo_h))
```
