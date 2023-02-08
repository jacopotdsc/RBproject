#include "localizer2d.h"

#include "icp/eigen_icp_2d.h"

Localizer2D::Localizer2D()
    : _map(nullptr),
      _laser_in_world(Eigen::Isometry2f::Identity()),
      _obst_tree_ptr(nullptr) {}

/**
 * @brief Set the internal map reference and constructs the KD-Tree containing
 * obstacles coordinates for fast access.
 *
 * @param map_
 */
void Localizer2D::setMap(std::shared_ptr<Map> map_) {
  // Set the internal map pointer
  _map = map_;
  /**
   * If the map is initialized, fill the _obst_vect vector with world
   * coordinates of all cells representing obstacles.
   * Finally instantiate the KD-Tree (obst_tree_ptr) on the vector.
   */
 
  //std::cerr << map_->rows() << std::endl;
  //std::cerr << _map->initialized() << std::endl;
  //std::cerr << ( _map->rows() != 0 )<< std::endl;

  
  if(_map->initialized() == 0){
    std::cerr << "-- map not initialized" << std::endl;
    return;
  }


  std::cerr << "-- initialized\n";

  cv::Mat world_map = _map->map();
  cv::Size2i matrix_size = _map->size();
  auto mat_rows = matrix_size.height;
  auto mat_cols = matrix_size.width;

  for( int r=0; r < mat_rows; r++){
    for( int c=0; c < mat_cols; c++){

      auto point_in_map = (*_map)(r,c);

      if(point_in_map == CellType::Occupied){
        Eigen::Vector2f converted_point = Eigen::Vector2f(r,c);
        _obst_vect.push_back(converted_point);
        
        std::cerr << converted_point << std::endl;
      }

    }

  }

  // Create KD-Tree
  // TODO
  
  using my_ContainerType = std::vector<Vector2f, Eigen::aligned_allocator<Vector2f> >;
  using TreeNodeType = TreeNode_<my_ContainerType::iterator>;

  TreeNodeType my_kd_tree(_obst_vect.begin(), _obst_vect.end(), 10);

  _obst_tree_ptr.reset( &my_kd_tree);



}

/**
 * @brief Set the current estimate for laser_in_world
 *
 * @param initial_pose_
 */
void Localizer2D::setInitialPose(const Eigen::Isometry2f& initial_pose_) {
  _laser_in_world = initial_pose_;
}

/**
 * @brief Process the input scan.
 * First creates a prediction using the current laser_in_world estimate
 *
 * @param scan_
 */
void Localizer2D::process(const ContainerType& scan_) {
  // Use initial pose to get a synthetic scan to compare with scan_
  // TODO

  /**
   * Align prediction and scan_ using ICP.
   * Set the current estimate of laser in world as initial guess (replace the
   * solver X before running ICP)
   */
  // TODO

  /**
   * Store the solver result (X) as the new laser_in_world estimate
   *
   */
  // TODO
}

/**
 * @brief Set the parameters of the laser scanner. Used to predict
 * measurements.
 * These parameters should be taken from the incoming sensor_msgs::LaserScan
 * message
 *
 * For further documentation, refer to:
 * http://docs.ros.org/en/noetic/api/sensor_msgs/html/msg/LaserScan.html
 *
 *
 * @param range_min_
 * @param range_max_
 * @param angle_min_
 * @param angle_max_
 * @param angle_increment_
 */
void Localizer2D::setLaserParams(float range_min_, float range_max_,
                                 float angle_min_, float angle_max_,
                                 float angle_increment_) {
  _range_min = range_min_;
  _range_max = range_max_;
  _angle_min = angle_min_;
  _angle_max = angle_max_;
  _angle_increment = angle_increment_;
}

/**
 * @brief Computes the predicted scan at the current laser_in_world pose
 * estimate.
 *
 * @param dest_ Output predicted scan
 */
void Localizer2D::getPrediction(ContainerType& prediction_) {
  prediction_.clear();
  /**
   * To compute the prediction, query the KD-Tree and search for all points
   * around the current laser_in_world estimate.
   * You may use additional sensor's informations to refine the prediction.
   */
  // TODO
}